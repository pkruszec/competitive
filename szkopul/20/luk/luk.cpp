#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<bool> vis;

int mi(int v)
{
    vis[v] = true;

    int r = 0;
    for (auto w: adj[v]) {
        if (!vis[w]) r++;
    }

    int mx = r;
    for (auto w: adj[v]) {
        if (!vis[w]) mx = max(mx, mi(w));
    }

    return mx;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    adj.resize(n + 1, vector<int>());
    vis.resize(n + 1, false);

    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    cout << mi(1) << "\n";

    return 0;
}
