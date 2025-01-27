#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;

struct Edge {
    int v, w, c;
};

int n, m;
vector<Edge> edg;
vector<bool> vis;
unordered_set<int> vv;

int dij(int s)
{
    vector<int> dist(n+1, -1);
    vector<int> prev(n+1, -1);

    int cnt = 0;

    using P = pair<int, int>;
    priority_queue<P, vector<P>, greater<P>> q;
    dist[s] = 0;
    q.push({s, 0});

    while (!q.empty()) {
        auto [v, d] = q.top();
        q.pop();
        if (d > dist[v]) continue;
        
        for (auto &[a, b, c]: edg) {
            int w;
            if (a == v) {
                w = b;
            } else if (b == v) {
                w = a;
            } else continue;

            if (dist[w] < 0 || dist[w] > dist[v] + c) {
                dist[w] = dist[v] + c;
                prev[w] = v;
                q.push({w, dist[w]});
            }
        }
    }

    // for (int i = 1; i <= n; ++i) {
    //     cout << prev[i] << "\n";
    // }

    return dist[n];
}

void dfs(int v, int max, vector<int> p, int cs=0)
{
    vis[v] = true;
    p.push_back(v);
    if (cs > max) return;

    if (v == n) {
        for (auto x: p) vv.insert(x);
        return;
    }

    for (auto &[x, y, c]: edg) {
        int u;
        if (x == v) {
            u = y;
        } else if (y == v) {
            u = x;
        } else {
            continue;
        }

        if (u != n && vis[u]) continue;
        dfs(u, max, p, cs + c);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    edg.resize(m);
    vis.resize(n+1);

    for (int i = 0; i < m; ++i) {
        auto &e = edg[i];
        cin >> e.v >> e.w >> e.c;
    }

    int max = dij(1);
    dfs(1, max, {});

    vector<int> tmp;
    for (auto x: vv) {
        tmp.push_back(x);
    }
    sort(tmp.begin(), tmp.end());
    for (auto x: tmp) {
        cout << x << "\n";
    }

    return 0;
}
