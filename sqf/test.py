import random

N = 3
n = 100000

in_path = "aga/aga_{0:02d}.in"
out_path = "out/aga_{0:02d}.out"

for i in range(1, N+1):
    k = random.randint(1, n)
    c = random.randint(1, n)

    print(i, k, c)

    s = n * [True]
    for cc in range(c):
        idx = random.randint(0, n-k)
        for cs in range(k):
            s[idx+cs] = not s[idx+cs]

    ss = "".join(["w" if c else "b" for c in s])

    with open(in_path.format(i), "w", encoding="utf-8") as f:
        f.write(f"{n} {k}\n")
        f.write(f"{ss}\n")

    with open(out_path.format(i), "w", encoding="utf-8") as f:
        f.write(f"{c}\n")
