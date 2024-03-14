def fib(n):
    a = 0
    b = 1
    for i in range(n):
        t = a
        a = b
        b = t+b
    return b

print(fib(4))