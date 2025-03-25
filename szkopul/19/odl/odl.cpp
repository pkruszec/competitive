#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits.h>
#include <math.h>
#include <queue>

using namespace std;

bool is_prime(int n)
{
    if (n <= 3) return true;

    int m = ceil(sqrt(n));
    for (int i = 2; i < m; ++i) {
        if (n % i == 0) return false;
    }

    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n+1);
    unordered_map<int, int> S;
    int M = 0;

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        xs[i] = x;
        M = max(M, x);
        if (S[x] == 0) {
            S[x] = i;
        }
    }

    vector<pair<int, int>> E;
    for (int i = 1; i <= M-1; ++i) {
        for (int j = 2; j <= M; ++j) {
            if ((i*j) > M) break;
            if (!is_prime(j)) continue;
            E.push_back({i, i*j});
        }
    }

    // cout << E.size() << "\n";

    // cout << "graph {\n";
    // for (auto &[a, b]: E) {
    //     cout << "    " << a << " -- " << b << "\n";
    // }
    // cout << "}\n";

    vector<int> ds(M+1, INT_MAX);
    vector<int> ms(M+1);

    queue<int> q;

    for (auto &[v, i]: S) {
        if (i == 0) continue;
        ds[v] = 0;
        ms[v] = v;
        q.push(v);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto &[a, b]: E) {
            int w;
            if (a == v) w = b;
            else if (b == v) w = a;
            else continue;

            if (ds[w] == INT_MAX) {
                ds[w] = ds[v] + 1;
                ms[w] = ms[v];
                q.push(w);
            } else if (ds[v]+1 == ds[w] && ms[v] < ms[w]) {
                ms[w] = ms[v];
            }
        }
    }

    vector<int> dv(M+1, INT_MAX);
    vector<int> mv(M+1, INT_MAX);

    for (auto &[v, w]: E) {
        // int w;
        // if (a == v) w = b;
        // else if (b == v) w = a;
        // else continue;

        int vv = ms[v];
        int ww = ms[w];
        if (vv != ww) {
            int d = ds[v] + 1 + ds[w];
            if (d < dv[vv] || (d == dv[vv] && ww < mv[vv])) {
                dv[vv] = d;
                mv[vv] = ww;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << mv[xs[i]] << "\n";
    }

    return 0;
}
