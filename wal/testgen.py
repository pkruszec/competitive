"""
n = 500
with open("input05.txt", "w", encoding="utf-8") as f:
    f.write(f"{n}\n")
    for i in range(n):
        f.write(f"{i+1} {n-i}\n")
"""

n1 = 100000
n2 = 100000
n = n1+n2

with open("input06.txt", "w", encoding="utf-8") as f:
    f.write(f"{n}\n")

    for i in range(n1):
        f.write(f"{i+1} {i+1}\n")

    for i in range(n2):
        x = (3*n//2) - i
        f.write(f"{i+1} {x}\n")
