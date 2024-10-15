import random

n = 250

def gen_yes(f):
    f.write(f"{n}\n")
    s = [i for i in range(1, n)]
    z = [i for i in range(1, n)]
    for i in range(n-2):
        idx = random.randint(0, len(s)-1)
        cs = s[idx]
        del s[idx]

        idx = random.randint(0, len(z)-1)
        cz = z[idx]
        del z[idx]

        f.write(f"{cs} {cz}\n")

    a = random.randint(n+2, 3*n)
    d = random.randint(n+2, 3*n)
    c = random.randint(n+1, a-1)
    b = random.randint(n+1, d-1)

    f.write(f"{a} {b}\n")
    f.write(f"{c} {d}\n")

def gen_inv(f):
    f.write(f"{n}\n")
    for i in range(n):
        f.write(f"{i+1} {n-i}\n")

for test in range(1, 21):
    with open(f"test/test_yes_250_{test:02d}.txt", "w", encoding="utf-8") as f:
        gen_yes(f)
