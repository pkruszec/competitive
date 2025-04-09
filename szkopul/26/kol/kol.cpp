#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

#define INF INT_MAX

struct Edge{
    int v, w, c;
};

vector<int> r;
vector<Edge> e;
int n;

vector<int> dijkstra(int src)
{
    vector<int> dist(n+1, INF);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({src, INF});
    
    while (!q.empty()) {
        auto [u, unused] = q.top();
        q.pop();
        for (auto &edge: e) {
            int v;
            if (edge.v == u) {
                v = edge.w;
            } else if (edge.w == u) {
                v = edge.v;
            } else {
                continue;
            }
            int c = edge.c;
            
            int alt = dist[u] + c;
            if (alt < dist[v]) {
                dist[v] = alt;
                q.push({v, alt});
            }
        }
    }
    
    return dist;
}

int cost(int a, int b, int c)
{
    vector<int> d1 = dijkstra(a);
    vector<int> d2 = dijkstra(b);
    
    int best = INF;
    for (int i = 1; i <= n; ++i) {
        if (r[i] != c) continue;
        if (d1[i] == INF) continue;
        if (d2[i] == INF) continue;
        
        if (d1[i]+d2[i] < best) {
            best = d1[i]+d2[i];
        }
    }
    if (best == INF) return -1;
    
    return best;
}

int main()  
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int m;
    cin >> n >> m;
    r.resize(n+1, 0);
    e.resize(n-1);
    for (int i = 1; i <= n; ++i) {
        cin >> r[i];
    }
    
    for (int i = 0; i < n-1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        e[i] = {a, b, c};
    }
    
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << cost(a, b, c) << "\n";
    }
    
    return 0;
}
