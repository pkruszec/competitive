import cp

import os
import filecmp
import subprocess
import shutil
import logging
import pathlib

logging.basicConfig(level=logging.INFO)

logger = logging.getLogger('cp')

def source_filename_to_exe(source):
    result = str(pathlib.Path(source).with_suffix(".exe"))
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

    if incremental:
        if not os.path.exists(folder):
            os.mkdir(folder)

        if os.path.exists(inc_file):
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

    if output is None:
        output = source
    
    outfile = source_filename_to_exe(output)
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

def run_with_file(prog, infile):
    cmd = [prog]
    logger.info(f"Running task: {' '.join(cmd)} with input {infile}")
    with open(infile, "rb") as f:
        process = subprocess.run(cmd, stdin=f)
        return process.returncode == 0

clean_folder()
if build_file("her.cpp"):
    run_with_file("her", "in/her/01.in")
