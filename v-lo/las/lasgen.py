import random

n = 1000
d = 1000
m = 10

def gen_check(f):
    f.write(f"{n} {d}\n")
    for i in range(n):
        for j in range(n):
            if j % 2 == i % 2:
                f.write(f"{m} ")
            else:
                f.write(f"0 ")
        f.write("\n")

def gen_rand(f):
    f.write(f"{n} {d}\n")
    for i in range(n):
        for j in range(n):
            f.write(f"{random.randint(1, m)} ")
        f.write("\n")

path = "06.in"
with open(path, "w", encoding="utf-8") as f:
    gen_rand(f)
