import random
import sys

def print_board(board, f=sys.stdout):
    for x in board:
        print("".join(x), file=f)

n = 1000
board = [n * ['#'] for i in range(n)]
checks = []

for y in range(1, n-1):
    for x in range(1, n-1):
        if random.random() < 0.6:
            board[y][x] = '.'
            checks.append((y, x))

random.shuffle(checks)
checks = checks[:n]

with open("05.in", "w", encoding="utf-8") as f:
    f.write(f"{n}\n")
    print_board(board, f)
    for (a, b) in checks:
        f.write(f"{a} {b}\n")
