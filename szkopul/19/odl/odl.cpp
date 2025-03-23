#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits.h>

using namespace std;

unordered_map<int, int> ft(int x)
{
    unordered_map<int, int> t;
    while (true) {
        if (x < 2) {
            t[x]++;
            break;
        }

        bool ok = false;
        for (int i = 2; i < x; ++i) {
            if (x % i == 0) {
                t[i]++;
                x /= i;
                ok = true;
                break;
            }
        }

        if (!ok) {
            t[x]++;
            break;
        }
    }
    return t;
}

int d(int x, int y)
{
    if (x % y == 0) {
        auto fs = ft(x/y);
        int s = 0;
        for (auto f: fs) {
            s += f.second;
        }
        return s;
    }

    if (y % x == 0) {
        auto fs = ft(y/x);
        int s = 0;
        for (auto f: fs) {
            s += f.second;
        }
        return s;
    }

    unordered_map<int, int> fx = ft(x);
    unordered_map<int, int> fy = ft(y);

    unordered_map<int, int> fs;
    for (auto f: fx) {
        if (fs[f.first] == 0) {
            fs[f.first] = abs(fx[f.first] - fy[f.first]);
        }
    }

    for (auto f: fy) {
        if (fs[f.first] == 0) {
            fs[f.first] = abs(fx[f.first] - fy[f.first]);
        }
    }

    // for (auto f: fs) {
    //     cout << f.first << ":" << f.second << " ";
    // }
    // cout << "\n";
    // for (auto f: fx) {
    //     cout << f.first << ":" << f.second << " ";
    // }
    // cout << "\n";
    // for (auto f: fy) {
    //     cout << f.first << ":" << f.second << " ";
    // }
    // cout << "\n";

    int s = 0;
    for (auto f: fs) {
        s += f.second;
    }

    return s;
}

int main()
{
    cout << d(1000000, 121219) << "\n";
    return 0;

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // cout << d(42, 69) << "\n";

    int n;
    cin >> n;
    vector<int> xs(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> xs[i];
    }

    for (int i = 1; i <= n; ++i) {
        int mi = 0;
        int md = INT_MAX;

        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            int di = d(xs[i], xs[j]);

            if (di < md) {
                mi = j;
                md = di;
            }
        }

        cout << mi << "\n";
    }

    // cout << "graph {\n";
    // for (int i = 1; i <= n - 1; ++i) {
    //     for (int j = i + 1; j <= n; ++j) {
    //         cout << "    " << xs[i] << " -- " << xs[j] << " [label=" << d(xs[i], xs[j]) << "]\n";
    //     }
    // }
    // cout << "}\n";

    return 0;
}

/*
    42, 69

    3*7*2
    23*3

    x * (23*3)/(3*7*2) = (23)/(7*2)

    5, 6
    2 * 3

    x * 2*3 / 5

    1,4

    *2*2

    To calculate d, we need to factorize both numbers and cancel out everything we can.
*/
