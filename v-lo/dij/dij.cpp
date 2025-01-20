#include <iostream>
#include <tuple>
#include <queue>
#include <vector>
#include <limits.h>

using namespace std;

int n, m;
vector<tuple<int, int, int>> e;

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

        for (auto &[a, b, c]: e) {
            int w;
            if (a == v) {
                w = b;
            } else if (b == v) {
                w = a;
            } else continue;

            if (dist[w] < 0 || dist[w] > dist[v] + c) {
                dist[w] = dist[v] + c;
                q.push({w, dist[w]});
            }
        }
    }

    return dist[n];
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    cin >> n >> m;
    e.resize(m);

    for (int i = 0; i < m; ++i) {
        int v, w, c;
        cin >> v >> w >> c;
        e[i] = {v, w, c};
    }

    cout << dij(1) << '\n';

    return 0;
}

