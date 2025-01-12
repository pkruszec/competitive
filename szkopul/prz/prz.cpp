#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits.h>

using namespace std;
using Edges = vector<pair<int, int>>;
using S64 = long long;

S64 mod = 1000000007ll;

Edges E;
int mbs = 0;
unordered_map<int, int> t;
int n, m, z;

bool connected(int x, int j)
{
    for (auto [v, w]: E) {
        if ((v == j && w == x) || (v == x && w == j)) {
            return true;
        }
    }
    return false;
}

bool has_neighboring_color(int j, int c, vector<int> &colors)
{
    for (auto [v, w]: E) {
        int o;
        if (v == j) {
            o = w;
        } else if (w == j) {
            o = v;
        } else continue;

        if (colors[o] == c) return true;
    }
    return false;
}

void pc(vector<int> &colors)
{
    cout << "{ ";
    for (int j = 1; j <= n; ++j) {
        cout << "[" << j << ": " << colors[j] << "] ";
    }
    cout << "}\n";
}

void f(int j, vector<int> colors, int max_color)
{

    if (j > n) {
        // pc(colors);

        t[max_color]++;
        if (max_color > mbs) mbs = max_color;
        return;
    }

    if (max_color > 0) {
        for (int i = 1; i <= max_color; ++i) {
            if (has_neighboring_color(j, i, colors)) continue;
            int old = colors[j];
            colors[j] = i;
            f(j + 1, colors, max_color);
            colors[j] = old;
        }
    }

    colors[j] = ++max_color;
    f(j + 1, colors, max_color);
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


    // for (auto [k, v]: t) {
    //     cout << k << ": " << v << "\n";
    // }

    f(1, vector<int>(n+1, 0), 0);

    for (int i = 0; i < z; ++i) {
        int k;
        cin >> k;
        cout << h(k) << '\n';
    }

    return 0;
}
