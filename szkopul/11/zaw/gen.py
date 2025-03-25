import random

n = 100
m = 100

print(f"{n} {m}")
for i in range(m):
    v = random.randint(1, n)
    w = random.randint(1, n)
    while w == v:
        w = random.randint(1, n)

    a = random.randint(1, n)
    b = random.randint(1, n)
    while a == b:
        b = random.randint(1, n)

    print(f"{v} {w} {a} {b}")
