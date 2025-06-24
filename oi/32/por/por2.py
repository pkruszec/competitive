from porlib import DajN, Zamiana

def main():
    for _ in range(DajN()):
        # Swap the first two elements.
        # Break if the number of inversions is zero.
        if Zamiana(1, 2) == 0:
            break

if __name__ == "__main__":
    main()
