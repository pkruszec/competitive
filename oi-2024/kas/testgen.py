import random

N = 1_000_000_000
template = "in/g{0:02d}.in"

for i in range(1, 10 + 1):
    with open(template.format(i), "w", encoding="utf-8") as f:
        f.write(str(random.randint(1, N)))
