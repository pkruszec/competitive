#!/usr/bin/env python3
import random

N = 10
M = 20
P = 10
B = 8

for i in range(N):
    with open(f"tests/test{str(i+1).zfill(3)}.txt", "w", encoding="utf-8") as f:
        n = random.randint(2, M)
        m = random.randint(1, M)
        f.write(f"{n} {m}\n")
        for j in range(n):
            f.write(f"{random.randint(B, P)} ")
        f.write("\n")

        a = random.randint(1, n)
        b = random.randint(1, n)
        while b == a:
            b = random.randint(1, n)

        f.write(f"{a} {b} {random.randint(1, B)}\n")

