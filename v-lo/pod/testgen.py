import sys
import random

def print_random(n: int, k: int, mi: int = 1, ma: int = 200):
    print(f"{n} {k}")
    for i in range(n):
        x = random.randint(mi, ma)
        print(f"{x} ", end="")

def print_all_same(n: int, k: int, x: int):
    print(f"{n} {k}")
    for i in range(n):
        print(f"{x} ", end="")

def main(args):
    print_random(1000, 1)
    # print_all_same(1000, 50, 42)

if __name__ == "__main__":
    args = sys.argv
    main(args)