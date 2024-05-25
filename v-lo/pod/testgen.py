import sys
import random

def print_random(n: int, k: int, mi: int = 1, ma: int = 200):
    print(f"{n} {k}")
    for i in range(n):
        x = random.randint(mi, ma)
        print(f"{x} ", end="")

def main(args):
    print_random(1000, 12)

if __name__ == "__main__":
    args = sys.argv
    main(args)