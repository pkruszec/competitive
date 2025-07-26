import random

n = 100

def rnd():
    return 1 if random.randint(1, 100) < 90 else 0

print(n)
for i in range(n):
    print("".join([str(rnd()) for i in range(n)]))
