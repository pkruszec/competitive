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

vector<int> search() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    vector<int> dist(n+1, INF);
    q.push({1, 0});
    dist[1] = 0;
    while (!q.empty()) {
        auto [u, p] = q.top();
        q.pop();
        for (auto [v, c]: g[u]) {
            int alt = dist[u] + c;
            if (alt < dist[v]) {
                dist[v] = alt;
                q.push({v, alt});
            }
        }
    }
    return dist;
}

typedef pair<vector<bool>, int> PP;

vector<int> bfs(int mc) {
    queue<pair<vector<int>, PP>> q;

    vector<bool> is(n+1, false);
    is[1] = true;
    q.push({{1}, {is, 0}});

    unordered_set<int> s;

    while (!q.empty()) {
        auto [path, pair] = q.front();
        auto [vis, uc] = pair;
        int u = path[path.size()-1];
        q.pop();

#if 0
        for (auto x: path) {
            cout << x << " ";
        }
        cout << "\n";
#endif
#if 1
        if (u == n) {
            for (auto x: path) {
                s.insert(x);
            }
            continue;
        }
#endif
        for (auto [v, c]: g[u]) {
            
            //if (u==8) {
            //    cout << v << "\n";
            //}

            if (vis[v]) continue;
            vis[v] = true;
            if (uc+c > mc) continue;
            path.push_back(v);
            q.push({path, {vis, uc+c}});
            path.pop_back();
        }
    }

    vector<int> res;
    for (auto x: s) res.push_back(x);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    g.resize(n+1);
    for (int i = 0; i < m; ++i) {
        int v,w,c;
        cin >> v >> w >> c;
        g[v].push_back({w, c});
        g[w].push_back({v, c});
    }

    auto d = search();
    auto p = bfs(d[n]);
    sort(p.begin(), p.end());

    for (auto x: p) {
        cout << x << "\n";
    }
    return 0;
}
