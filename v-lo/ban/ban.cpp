#include <iostream>

#define MAX_N 30001

/*
1  - 4
2  - 10
3  - 7
4  - 3
5  - 2
6  - 6
7  - 1
8  - 5
9  - 11
10 - 8
11 - 12
12 - 9
*/

struct Node {
    int prev;
    int next;
};

#ifndef UNIT_TESTING
int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n;
    std::cin >> n;

    Node guests[MAX_N] = {0};
    bool flagged[MAX_N] = {0};

    for (int i = 1; i <= n; ++i) {
        int k;
        std::cin >> k;

        guests[i].prev = k;
        guests[k].next = i;
    }

    int tables = 0;
    for (int i = 1; i <= n; ++i) {
        if (flagged[i]) continue;

        int k = guests[i].prev;
        while (k != i) {
            flagged[k] = true;
            k = guests[k].prev;
        }

        tables += 1;
    }

    std::cout << tables << "\n";

    return 0;
}
#endif // UNIT_TESTING