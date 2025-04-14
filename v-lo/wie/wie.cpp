#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <limits.h>
#include <algorithm>
using namespace std;

#define INF (1000000000)

int n, m;
vector<vector<pair<int, int>>> g;

void search(vector<int> &dist) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({1, 0});
    dist[1] = 0;
    while (!q.empty()) {
        auto [u, p] = q.top();
        q.pop();
        if (p > dist[u]) continue;
        for (auto [v, c]: g[u]) {
            int alt = dist[u] + c;
            if (alt < dist[v]) {
                dist[v] = alt;
                q.push({v, alt});
            }
        }
    }
}

vector<bool> bfs(vector<int> &dist) {
    vector<bool> p(n+1, false);
    vector<vector<int>> rg(n+1);

    for (int v = 1; v <= n; ++v) {
        for (auto [u, c]: g[v]) {
            if (dist[u] + c == dist[v]) {
                rg[v].push_back(u);
            }
        }
    }

    queue<int> q;
    q.push(n);
    p[n] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v: rg[u]) {
            if (!p[v]) {
                p[v] = true;
                q.push(v);
            }
        }
    }

    return p;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    g.resize(n+1);
    vector<int> dist(n+1, INF);
    for (int i = 0; i < m; ++i) {
        int v,w,c;
        cin >> v >> w >> c;
        g[v].push_back({w, c});
        g[w].push_back({v, c});
    }

    search(dist);
    auto p = bfs(dist);

    for (int i = 1; i <= n; ++i) {
        if (p[i]) cout << i << "\n";
    }

    return 0;
}
