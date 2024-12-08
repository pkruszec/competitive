import random

n = 1000
d = 1000
m = 1_000_000_000
path = "05.in"

with open(path, "w", encoding="utf-8") as f:
    f.write(f"{n} {d}\n")
    for i in range(n):
        for j in range(n):
            f.write(f"{random.randint(1, m)} ")
        f.write("\n")
