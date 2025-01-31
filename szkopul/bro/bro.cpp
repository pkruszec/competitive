#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    uint64_t n;
    cin >> n;

    vector<uint64_t> z(n+1);
    vector<uint64_t> d(n+1);
    for (uint64_t i = 1; i <= n; ++i) {
        cin >> z[i] >> d[i];
    }

    uint64_t i = 1;
    uint64_t r = 1;
    uint64_t l = 2;
    uint64_t zr = 0;
    uint64_t zl = 0;
    uint64_t dr = 0;
    uint64_t dl = 0;
    uint64_t c = 0;

    auto fix = [&]() {
        while (dr + d[r] < dl) {
            c += z[l] * (dr + d[r] - dl);
            zr += z[l];
            zl -= z[l];
            dr += d[r];
            dl -= d[l];
            r = (r%n) + 1;
            l = (l%n) + 1;
        }
    };

    for (uint64_t i = n; i >= 2; --i) {
        dl += d[i];
        zl += z[i];
        c += dl*z[i];
    }

    fix();
    uint64_t cm = c;

    for (uint64_t i = 2; i <= n; ++i) {
        uint64_t dp = d[i - 1];
        c -= dp*(zr - (zl + z[i - 1]));
        zr -= z[i];
        zl += z[i - 1];
        dr -= dp;
        dl += dp;
        fix();
        cm = min(cm, c);
    }

    cout << cm << "\n";

    return 0;
}