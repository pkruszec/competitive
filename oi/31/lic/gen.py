n = 150_000
m = 2
print(n, m)
print(' '.join(['1' for i in range(n)]))
print(' '.join([str((i+1)*2) for i in range(n)]))
for i in range(m):
    print(' '.join([str((i+1)*(j+1)) for j in range(n)]))
