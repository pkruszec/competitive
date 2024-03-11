import sys
import random

if __name__ == "__main__":
    count = int(sys.argv[1])
    max_s = 1000000
    max_p = 30

    print(count)
    for i in range(count):
        s = random.randint(1, max_s)
        p = random.randint(1, max_p)
        print(f"{s} {p}")