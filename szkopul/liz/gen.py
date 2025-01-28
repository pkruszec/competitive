import random

n = 10_000
k = 10_000
path = "04.in"

with open(path, "w", encoding="utf-8") as f:
    f.write(f"{n} {k}\n")
    f.write("".join(
        "T" if random.randint(0, 1) == 0 else "W"
        for i in range(n)
    ))
    f.write("\n")
    f.write("\n".join(
        str(random.randint(1, n))
        for i in range(k)
    ))
    f.write("\n")
