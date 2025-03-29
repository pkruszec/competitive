#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef vector<vector<int>> adj;
typedef vector<bool> vis;
typedef vector<unordered_map<int, int>> ss;
typedef vector<int> ssc;

bool trav(ssc &sc, ss &s, vis &t, adj &g, ll v=1, ll p=0, ll cs=-1)
{
    if (t[v]) return true;
    if (p == 0) {
        s.push_back({});
        sc.push_back(0);
        cs = s.size() - 1;
    }

    t[v] = true;
    ll big_w_count = 0;
    for (auto w: g[v]) {
        if (t[w]) {
            if (w != p) return false;
            continue;
        }
        if (!trav(sc, s, t, g, w, v, cs)) return false;

        if (g[w].size() > 1) {
            big_w_count++;
        } else {
            s[cs][v]++;
        }
    }

    if (g[v].size() > 1) sc[cs]++;
    return big_w_count <= 2;
}

ll fact_k(ll x, ll k)
{
    ll y = 1;
    for (ll i = 1; i <= x; ++i) {
        y = ((y % k)*(i % k)) % k;
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
    adj graph(n + 1);
    vis visited(n + 1, false);
    ss s;
    ssc sc;

    for (ll i = 0; i < m; ++i) {
        ll v, w;
        cin >> v >> w;

        graph[v].push_back(w);
        graph[w].push_back(v);
    }

    // for (ll v = 1; v <= n; ++v) {
    //     cout << v << ": ";
    //     for (auto w: graph[v]) {
    //         cout << w << " ";
    //     }
    //     cout << "\n";
    // }

    for (ll v = 1; v <= n; ++v) {
        if (!trav(sc, s, visited, graph, v)) {
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
        W = ((W%k) * (w+i)%k) % k;
    }

    ll L = 1;
    for (ll i = 0; i < s.size(); ++i) {
        if (sc[i] == 0) continue;

        ll ct = sc[i] > 2 ? 4 : 2;
        ll ls = 1;
        for (auto pr: s[i]) {
            ls = ((ls%k) * fact_k(pr.second, k)) % k;
        }

        L = ((((L%k) * (ct%k)) % k) * (ls%k)) % k;
    }

    ll r = ((((L%k) * fact_k(P, k)) % k) * W) % k;

    // cout << "S=" << S << "\n";
    // cout << "P=" << P << "\n";
    // cout << "w=" << w << "\n\n";
    // cout << "W=" << W << "\n";

    cout << r << "\n";

    return 0;
}
