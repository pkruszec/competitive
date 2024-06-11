import random
import subprocess

DIR = "./tests/"
INP_EXT = ".txt"
EXP_EXT = ".exp.txt"
UNIT_PATH = "./build/unit.exe"

def gen_test(stem):
    dir_plus_stem = DIR + stem
    inp_path = dir_plus_stem + INP_EXT
    exp_path = dir_plus_stem + EXP_EXT

    n = 10
    m = 30

    with open(inp_path, "w") as f:
        f.write(f"{n} {m}\n")
        for i in range(m):
            r = random.randint(1, n+1)
            f.write(f"{r} ")

    with open(exp_path, "w") as f:
        subprocess.run([UNIT_PATH, "stable", inp_path], stdout=f)

def main():
    prefix = "testpy_"
    for i in range(11, 21):
        stem = prefix + str(i)
        print(stem)
        gen_test(stem)

if __name__ == "__main__":
    main()
