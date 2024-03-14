import sys
import random

if __name__ == "__main__":
    count = int(sys.argv[1])
    max_x = 1000000

    print(count)
    for i in range(count):
        x = random.randint(1, max_x)
        print(f"{x}")