#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using Edges = vector<pair<int, int>>;
using Buckets = vector<vector<int>>;
using S64 = long long;

S64 mod = 1000000007ll;

Edges E;
int mbs = 0;
unordered_map<int, int> t;
int n, m, z;

void pb(Buckets &buckets)
{
    cout << "bx {\n";
    for (auto bx: buckets) {
        cout << "  { ";
        for (auto b: bx) {
            cout << b << " ";
        }
        cout << "}\n";
    }
    cout << "}\n";
}

bool connected(int x, int j)
{
    for (auto [v, w]: E) {
        if ((v == j && w == x) || (v == x && w == j)) {
            return true;
        }
    }
    return false;
}

void f(int j, Buckets buckets)
{
    if (j > n) {
        t[buckets.size()]++;
        if (buckets.size() > mbs) mbs = buckets.size();
        return;
    }

    for (auto &b: buckets) {
        bool found = false;
        for (auto x: b) {
            if (connected(x, j)) {
                found = true;
                break;
            }
        }

        if (found) continue;
        b.push_back(j);
        f(j + 1, buckets);
        b.pop_back();
    }

    vector<int> b = {j};
    buckets.push_back(b);
    f(j + 1, buckets);
}

S64 h(S64 k)
{
    if (k == 1) return 0;

    S64 s = 0;
    for (int i = 0; i <= mbs; ++i) {
        int x = t[i];
        if (x == 0) continue;

        S64 p = x;
        // cout << p << "\n";
        for (int j = 0; j < i; ++j) {
            p = ((p) * ((k-j))) % mod;
        }

        s = (s + p) % mod;
    }
    return s;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> z;
    E.resize(m);

    for (int i = 0; i < m; ++i) {
        int v, w;
        cin >> v >> w;
        E[i] = {v, w};
    }

    f(1, {});

    // for (auto [k, v]: t) {
    //     cout << k << ": " << v << "\n";
    // }

    for (int i = 0; i < z; ++i) {
        S64 k;
        cin >> k;

        cout << h(k) << '\n';
    }

    return 0;
}
