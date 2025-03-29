#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef vector<pair<int, int>> edg;
typedef vector<bool> vis;
typedef vector<unordered_map<int, int>> ss;
typedef vector<int> ssc;

bool trav(ssc &sz, ssc &sc, ss &s, vis &t, edg &g, ll v=1, ll p=0, ll cs=-1)
{
    if (t[v]) return true;
    if (p == 0) {
        s.push_back({});
        sc.push_back(0);
        cs = s.size() - 1;
    }

    t[v] = true;
    ll big_w_count = 0;
    for (auto &[a, b]: g) {
        int w;
        if (a == v) w = b;
        else if (b == v) w = a;
        else continue;

        if (t[w]) {
            if (w != p) return false;
            continue;
        }
        if (!trav(sz, sc, s, t, g, w, v, cs)) return false;

        if (sz[w] > 1) {
            big_w_count++;
            if (big_w_count > 2) return false;
        } else {
            s[cs][v]++;
        }
    }

    if (sz[v] > 1) sc[cs]++;
    return big_w_count <= 2;
}

ll fact_k(ll x, ll k)
{
    ll y = 1;
    for (ll i = 1; i <= x; ++i) {
        y = ((y)*(i % k)) % k;
    }
    return y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m, k;
    cin >> n >> m >> k;
    if (m >= n) {
        cout << "0\n";
        return 0;
    }
    edg graph(m);
    vis visited(n + 1, false);
    ss s;
    ssc sc;
    ssc sz(n + 1);

    for (ll i = 0; i < m; ++i) {
        ll v, w;
        cin >> v >> w;

        graph[i] = {v, w};
        sz[v]++;
        sz[w]++;
    }

    // for (ll v = 1; v <= n; ++v) {
    //     cout << v << ": ";
    //     for (auto w: graph[v]) {
    //         cout << w << " ";
    //     }
    //     cout << "\n";
    // }

    for (ll v = 1; v <= n; ++v) {
        if (!trav(sz, sc, s, visited, graph, v)) {
            cout << "0\n";
            return 0;
        }
    }

    // for (ll i = 0; i < s.size(); ++i) {
    //     cout << i << " (" << sc[i] << ")\n";
    //     for (auto &[k, v]: s[i]) {
    //         cout << "  " << k << " => " << v << "\n";
    //     }
    // }

    ll S = 0;
    for (auto x: sc) {
        if (x == 0) S++;
    }
    ll P = s.size() - S;
    ll w = (n - S) % k;

    ll W = 1;
    for (ll i = 0; i < S; ++i) {
        W = (W * ((w+(i)%k)%k)) % k;
    }

    ll L = 1;
    for (ll i = 0; i < s.size(); ++i) {
        if (sc[i] == 0) continue;

        ll ct = sc[i] > 2 ? 4 : 2;
        ll ls = 1;
        for (auto pr: s[i]) {
            ls = (ls * fact_k(pr.second, k)) % k;
        }

        L = (((L * (ct%k)) % k) * (ls%k)) % k;
    }

    ll r = (((L * fact_k(P, k)) % k) * W) % k;

    // cout << "S=" << S << "\n";
    // cout << "P=" << P << "\n";
    // cout << "w=" << w << "\n\n";
    // cout << "W=" << W << "\n";

    cout << r << "\n";

    return 0;
}
