#!/usr/bin/env python3

def main():
    # Read the size of the permutation.
    n = int(input())
    for _ in range(10):
        # Swap the first two elements.
        print("1 2", flush=True)
        # Read the number of inversions from the simulator.
        inversions = int(input())
        if inversions == 0:
            break

if __name__ == "__main__":
    main()
