import random

n = 20
print(n)
for i in range(n):
    print( " ".join([str(random.randint(1, 1000)) for j in range(n)]) )
