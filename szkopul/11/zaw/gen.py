import random

n = 5000
m = 4999

print(f"{n} {m}")
for i in range(m):
    v = i + 1
    w = v + 1

    a = random.randint(1, n)
    b = random.randint(1, n)
    while a == b:
        b = random.randint(1, n)
    print(f"{v} {w} {a} {b}")
