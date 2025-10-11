import os
import filecmp
import subprocess
import shutil
import logging
import pathlib
import glob
import csv

logging.basicConfig(level=logging.INFO)

logger = logging.getLogger('cp')

def source_filename_to_exe(source):
    result = source
    if os.name == "nt":
        result = str(pathlib.Path(source).with_suffix(".exe"))
    else:
        result = str(pathlib.Path(source).with_suffix(".out"))
    return result

def clean_folder(folder=None):
    if folder is None:
        folder = "."

    exts = {".ilk", ".pdb", ".obj", ".lib"}
    path = pathlib.Path(folder)
    logger.info(f"Cleaning folder {path}")
    for p in path.iterdir():
        if p.suffix.lower() in exts and p.is_file():
            p.unlink()

def build_file(source, compiler=None, output=None, fast=False, incremental=True):
    folder = ".cp"
    inc_file = f"{folder}/{source}.inc"

    if output is None:
        output = source
    outfile = source_filename_to_exe(output)

    if incremental:
        if not os.path.exists(folder):
            os.mkdir(folder)

        if os.path.exists(inc_file) and os.path.exists(outfile):
            if filecmp.cmp(source, inc_file, shallow=False):
                return True

    if compiler is None:
        if shutil.which("g++") is not None:
            compiler = "g++"
        elif os.name == "nt" and shutil.which("cl") is not None:
            compiler = "cl"
        elif shutil.which("clang++"):
            compiler = "clang++"
        elif shutil.which("c++"):
            compiler = "c++"

    if compiler is None:
        logger.error("Could not find any supported C++ compiler to run.")
        return False

    cmd = [compiler]

    if compiler == "cl":
        cmd += ["-EHsc", "-Zi", "-nologo", "-std:c++17"]
        if fast:
            cmd += ["-O2"]
        cmd.append(source)
        cmd.append(f"/Fe{outfile}")
    else:
        cmd += ["-Wall", "-Wextra", "-std=c++17", "-g"]
        if fast:
            cmd += ["-O3"]
        cmd.append(source)
        cmd += ["-o", outfile]

    logger.info(f"Running compiler: {' '.join(cmd)}")

    process = subprocess.run(cmd)
    success = process.returncode == 0

    if incremental and success:
        logger.info(f"Copying file: {source} to {inc_file}")
        shutil.copyfile(source, inc_file)

    return success

def run_with_file(prog, infile, timeout=5.0):
    cmd = [prog]
    logger.info(f"Running task: {' '.join(cmd)} with input {infile}")
    with open(infile, "rb") as f:
        process = subprocess.run(cmd, stdin=f, timeout=timeout)
        return process.returncode == 0

def sio2jail_with_file(prog, infile, timeout=5.0):
    us = int(timeout * 1_000_000)

    sio2jail = shutil.which("sio2jail")
    if sio2jail is None:
        logger.error("sio2jail not found.")
        return

    cmd = [sio2jail, "--ustimelimit", f"{us}u", "-o", "human", "--mount-namespace", "off", prog]
    logger.info(f"Running {' '.join(cmd)} with input {infile}")
    with open(infile, "rb") as f:
        process = subprocess.run(cmd, stdin=f)
        return process.returncode == 0

def sio2jail_run_tests(prog, pattern, outdir, report_path=None, timeout=5.0):
    us = int(timeout * 1_000_000)

    sio2jail = shutil.which("sio2jail")
    if sio2jail is None:
        logger.error("sio2jail not found.")
        return

    processes = []

    outpath = pathlib.Path(outdir)
    for ps in glob.glob(pattern):
        path = pathlib.Path(ps)
        out = outpath.joinpath(path.with_suffix(".out").name)

        cmd = [sio2jail, "--rtimelimit", f"{us}u", "-o", "oireal", "--mount-namespace", "off", prog]

        with open(path, "rb") as f:
            p = subprocess.Popen(cmd, stdin=f, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            processes.append((p, path, out))

    logger.info(f"Running {len(processes)} tests")

    results = []
    passed_count = 0

    for p, path, out in processes:
        stdout, stderr = p.communicate()

        report_lines = stderr.splitlines()
        report = report_lines[0].split() + [report_lines[1]]

        with open(out, "r", encoding="utf-8") as f:
            expected = f.read().strip()

        correct = stdout.strip() == expected

        if report[0] == "OK" and not correct:
            tmp = out.with_suffix(".tmp")
            with open(tmp, "w", encoding="utf-8") as f:
                f.write(stdout)

        passed = correct and report[0] == "OK"
        passed_count += int(passed)
        results.append((path, out, passed, report))

    if report_path is not None:
        with open(report_path, "w", encoding="utf-8", newline="") as f:
            writer = csv.writer(f)
            writer.writerow(["No", "In", "Out", "Passed", "Status", "Code", "MsElapsed", "Zero", "PeakKB", "Syscalls", "Reason"])
            
            key = lambda x: x[0]
            results.sort(key=key)
            for i, (path, out, passed, report) in enumerate(results):
                row = [i+1, path, out, int(passed)] + report
                writer.writerow(row)

    logger.info("Testing done")
    logger.info("------------------------")
    logger.info(f"     FAILED: {len(processes) - passed_count}")
    logger.info(f"     PASSED: {passed_count}")
    logger.info(f"     TOTAL:  {len(processes)}")

