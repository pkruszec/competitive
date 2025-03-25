#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>

using namespace std;

struct T {
    int v;
    int c;
};

void dijkstra(vector<vector<T>> &adj, vector<int> &dist, vector<int> &prv)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    dist[1] = 0;
    q.push({1, 0});

    while (!q.empty()) {
        auto u = q.top().first;
        q.pop();

        for (auto a: adj[u]) {
            int v = a.v;
            int e = a.c;

            int alt = dist[u] + e;
            if (alt < dist[v]) {
                prv[v] = u;
                dist[v] = alt;
                q.push({v, dist[v]});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<T>> Adj(n + 1);
    vector<vector<T>> Odw(n + 1);
    vector<int> D(n + 1, INT_MAX);
    vector<int> H(n + 1, INT_MAX);
    vector<int> Prev(n + 1, INT_MAX);
    vector<int> Verp(n + 1, INT_MAX);
    vector<int> P(n + 1);

    for (int i = 0; i < m; ++i) {
        int v, w, vw, wv;
        cin >> v >> w >> vw >> wv;

        Adj[v].push_back({w, vw});
        Adj[w].push_back({v, wv});

        Odw[v].push_back({w, wv});
        Odw[w].push_back({v, vw});
    }

    dijkstra(Adj, D, Prev);
    dijkstra(Odw, H, Verp);

    // for (int i = 1; i <= n; ++i) {
    //     cout << "H[" << i << "] = " << H[i] << "\n";
    // }

    for (int i = 2; i <= n; ++i) {
        int pv = i;
        while (1) {
            int old = pv;
            pv = Prev[pv];
            if (pv == INT_MAX) {
                break;
            }

            // cout << old << ": " << pv << "\n";
            if (pv == 1) {
                P[i] = old;
                break;
            }
        }
    }

    P[1] = 1;

    int value = INT_MAX;
    for (int v = 1; v <= n; ++v) {
        for (auto &t: Adj[v]) {
            int w = t.v;
            int cost = t.c;
            int sm = D[v] + cost + H[w];

            if ((P[v] != v || P[w] != w) && P[v] != P[w]) {
                value = min(value, sm);
                // cout << v << " -> " << w << " (" << P[v] << ", " << P[w] << "): " << D[v] << "+" << cost << "+" << H[w] << " = " << sm << "\n";
            }
        }
    }
    cout << value << "\n";

    // for (int i = 2; i <= n; ++i) {
    //     cout << "P[" << i << "] = " << P[i] << "\n";
    // }

    return 0;
}
