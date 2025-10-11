#!/usr/bin/env python3
import random

for i in range(100):
    x = random.randint(1, 1_000_000_000)
    y = random.randint(1, 1_000_000_000)
    with open(f"xpl/in/gen_{i+1:03d}.in", "w", encoding="utf-8") as f:
        f.write(f"{x} {y}\n")

    with open(f"xpl/out/gen_{i+1:03d}.out", "w", encoding="utf-8") as f:
        f.write(f"{x+y}\n")


