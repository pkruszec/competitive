#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <stdint.h>

using namespace std;

/*

3 -> 1
4 -> 4

n!/k!(n-k)!

*/

vector<uint64_t> e;

uint64_t fact(uint64_t a)
{
    if (a == 0) return 1;

    uint64_t x = 1;
    for (uint64_t i = 1; i <= a; ++i) {
        x *= i;
    }
    return x;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    uint64_t n, m;
    cin >> n >> m;

    e.resize(n+1);

    for (uint64_t i = 0; i < m; ++i) {
        uint64_t p, k;
        cin >> p >> k;

        e[p]++;
        e[k]++;
    }

    uint64_t j = n*(n-1)*(n-2) / 6;

    uint64_t s = 0;
    for (uint64_t i = 1; i <= n; ++i) {
        s += (e[i] * (n-1-e[i])) / 2;
    }

    cout << j-s << "\n";

    return 0;
}
