n = 18
s = 7
print(n, s)
for i in range(1, n):
    if i%2 != 0:
        print(i, i+1)
    else:
        print(i+1, i)
