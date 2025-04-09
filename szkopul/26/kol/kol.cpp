#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

#define INF LLONG_MAX
#define ll long long

vector<ll> r;
vector<vector<pair<ll, ll>>> g;
ll n;
vector<vector<ll>> dij;

vector<ll> dijkstra(ll src)
{
    vector<ll> dist(n+1, INF);
    dist[src] = 0;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
    q.push({src, INF});
    
    while (!q.empty()) {
        auto [u, unused] = q.top();
        q.pop();
        for (auto &[v, c]: g[u]) {
            ll alt = dist[u] + c;
            if (alt < dist[v]) {
                dist[v] = alt;
                q.push({v, alt});
            }
        }
    }
    
    return dist;
}

ll cost(ll a, ll b, ll c)
{
    //vector<ll> d1 = dijkstra(a);
    //vector<ll> d2 = dijkstra(b);
    auto &d1 = dij[a];
    auto &d2 = dij[b];

    ll best = INF;
    for (ll i = 1; i <= n; ++i) {
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
    
    ll m;
    cin >> n >> m;
    r.resize(n+1, 0);
    g.resize(n+1);
    dij.resize(n+1);
    for (ll i = 1; i <= n; ++i) {
        cin >> r[i];
    }
    
    for (ll i = 0; i < n-1; ++i) {
        ll a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    
    for (ll i = 1; i <= n; ++i) {
        dij[i] = dijkstra(i);
    }

    ll q;
    cin >> q;
    for (ll i = 0; i < q; ++i) {
        ll a, b, c;
        cin >> a >> b >> c;
        cout << cost(a, b, c) << "\n";
    }
    
    return 0;
}
