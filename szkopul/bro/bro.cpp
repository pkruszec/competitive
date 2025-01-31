#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <limits.h>
#include <stdint.h>

using namespace std;

uint64_t n;
vector<uint64_t> P;
vector<uint64_t> C;

uint64_t distance(uint64_t x, uint64_t y)
{
    if (x == y) return 0;

    auto right = [&](uint64_t &i) {
        if (i >= n) {
            i = 1;
        } else {
            i++;
        }
    };

    uint64_t a = min(x, y);
    uint64_t b = max(x, y);

    uint64_t dl = 0;
    uint64_t dr = 0;

    for (uint64_t i = a; i != b; right(i)) {
        dr += C[i];
    }

    for (uint64_t i = b; i != a; right(i)) {
        dl += C[i];
    }

    return min(dl, dr);
}

uint64_t cost(uint64_t b)
{
    uint64_t c = 0;
    for (uint64_t i = 1; i <= n; ++i) {
        c += P[i] * distance(i, b);
    }
    return c;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;

    P.resize(n+1);
    C.resize(n+1);

    for (uint64_t i = 1; i <= n; ++i) {
        uint64_t p, c;
        cin >> p >> c;
        P[i] = p;
        C[i] = c;
    }

    uint64_t result = UINT64_MAX;
    for (uint64_t i = 1; i <= n; ++i) {
        result = min(result, cost(i));
    }

    cout << result << "\n";

    return 0;
}
