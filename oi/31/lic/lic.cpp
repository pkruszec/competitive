#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <limits.h>
#include <stdint.h>

using namespace std;

typedef long long s64;

#define REP(i, n) for (s64 i = 0; i < (n); ++i)
#define IT(xs)    for (auto &it: (xs))

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    s64 n, m;
    cin >> n >> m;

    vector<s64> c(n);
    vector<s64> s(n);
    // vector<vector<s64>> mc(m, vector<s64>(n));

    REP(i, n) cin >> c[i];
    REP(i, n) cin >> s[i];

    vector<s64> idx(n);
    REP(i, n) idx[i] = i;

    sort(idx.begin(), idx.end(), [&](auto a, auto b) {
        return c[a] > c[b];
    });

    s64 total = 0;

    auto s0 = s;

    REP(i, m) {
        multiset<s64> od;
        REP(j, n) {
            s64 x;
            cin >> x;
            od.insert(x);
        }

        bool ok = true;
        s64 sm = 0;

        REP(j, n) {
            s64 d = idx[j];
            //cout << j << "] = " << d << "(" << s[d] << ")\n";

            auto it = od.lower_bound(s[d]);
            if (it == od.end()) {
                ok = false;
                break;
            }
            if (i==m-1) {
                //cout << *it << ", " << s[d] << ", "<< c[d] << "\n";
            }
            sm += (*it - s0[d]) * c[d];
            s[d] = *it;
            od.erase(it);
        }

        if (!ok) {
            cout << "NIE\n";
            return 0;
        }

        if (i == m-1) total = sm;
    }

    cout << total << "\n";

    return 0;
}
