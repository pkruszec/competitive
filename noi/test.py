import random

h = 500
w = 500
n = 10
path = "test/sq500_lot_{0:02d}.in"
c = "llls"

for i in range(1, n+1):
    with open(path.format(i), "w", encoding="utf-8") as f:
        f.write(f"{h} {w}\n")
        for y in range(h):
            s = "".join([c[random.randint(0, len(c)-1)] for i in range(w)])
            f.write(f"{s}\n")

