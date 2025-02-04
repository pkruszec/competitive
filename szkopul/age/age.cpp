#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

int n, m;

vector<vector<int>> adj;

struct State {
    int v1, v2;
    int t;
    bool prime;
};

int bfs(int a1, int a2)
{
    queue<State> q;
    q.push({a1, a2, 0, false});

    vector<vector<bool>> vis(n+1, vector<bool>(n+1, false));
    vector<vector<bool>> vis_s(n+1, vector<bool>(n+1, false));

    while (!q.empty()) {
        auto s = q.front();
        q.pop();
        if (!s.prime && s.v1 == s.v2) return s.t / 2;

        if (!s.prime) {
            for (auto u: adj[s.v1]) {
                if (vis_s[u][s.v2]) continue;
                q.push({u, s.v2, s.t + 1, true});

                vis_s[u][s.v2] = true;
                // for (auto w: adj[s.v2]) {
                // }
            }
        } else {
            for (auto w: adj[s.v2]) {
                if (vis[s.v1][w]) continue;
                q.push({s.v1, w, s.t + 1, false});
                vis[s.v1][w] = true;
            }
        }

        // for (auto u: adj[v1]) {
        //     for (auto w: adj[v2]) {
        //         if (vis[u][w]) continue;
        //         q.push({{u, w}, t + 1});
        //         vis[u][w] = true;
        //     }
        // }
    }

    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int a1, a2;
    cin >> n >> m >> a1 >> a2;

    adj.resize(n+1);

    for (int i = 0; i < m; ++i) {
        int v, w;
        cin >> v >> w;
        adj[v].push_back(w);
    }

    int res = bfs(a1, a2);
    if (res < 0) {
        cout << "NIE\n";
    } else {
        cout << res << "\n";
    }

    return 0;
}
