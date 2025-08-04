#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits.h>

using namespace std;
using s64 = long long;

s64 in[100002] = {};
s64 f[100002] = {};

// int f(int i) {
//     if (i == 0) return 0;
//     if (i == 1) return in[1];
//     return max(f(i - 1), f(i - 2) + i * in[i]);
// }

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    // vector<s64> in(100002, 0);
    // vector<s64> f(100002, 0);

    int m = n;
    while (m--) {
        s64 x;
        cin >> x;
        in[x] += 1;
    }

    // cout << 100000 * in[100000] << "\n";

    f[0] = 0;
    f[1] = in[1];
    for (s64 i = 2; i <= 100000; ++i) {
        f[i] = max(f[i - 1], f[i - 2] + i * in[i]);

        // if (in[i] != 0) cout << "in[" << i << "] = " << in[i] << "\n"
    }

    cout << f[100000] << "\n";

    return 0;
}
