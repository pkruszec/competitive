import random

n = 10

for test in range(1, 11):
    with open(f"test/test{test:02d}.txt", "w", encoding="utf-8") as f:
        f.write(f"{n}\n")
        s = [i for i in range(1, n+1)]
        z = [i for i in range(1, n+1)]
        for i in range(n):
            idx = random.randint(0, len(s)-1)
            cs = s[idx]
            del s[idx]

            idx = random.randint(0, len(z)-1)
            cz = z[idx]
            del z[idx]

            f.write(f"{cs} {cz}\n")

