import math

def find1(x):
    for i in range(2, x):
        if x % i != 0:
            continue
        for j in range(2, x):
            if x % j != 0:
                continue

            if math.gcd(i+j, x) == 1:
                return (i, j)

    return (-1, -1)

def find2(x):
    div = [i for i in range(2, x) if x % i == 0]
    for i in div:
        for j in div:
            if math.gcd(i+j, x) == 1:
                return (i, j)

    return (-1, -1)

def find3(x):
    for i in range(2, x):
        if x % i != 0:
            continue
        for j in range(x, 1, -1):
            if x % j != 0:
                continue

            if math.gcd(i+j, x) == 1:
                return (i, j)

    return (-1, -1)

_ = input()
xs = [int(x) for x in input().split()]

res = [find3(x) for x in xs]
print(' '.join((str(x[0]) for x in res)))
print(' '.join((str(x[1]) for x in res)))
