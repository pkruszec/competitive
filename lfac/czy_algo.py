def check(n):
    it = 0
    while n > 1:
        it += 1
        if it > 1000:
            return False

        if n % 2 == 0:
            n /= 2
        else:
            n = 3*(n+1)

    return True

series = [check(i) for i in range(2, 100)]
for i, n in enumerate(series):
    print(2+i, n)

# 1  3  7  15
#   +2 +4  +8
