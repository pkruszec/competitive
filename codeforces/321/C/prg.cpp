#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int n, m;
vector<bool> cat;
vector<vector<int>> adj;
int cnt = 0;

void trav(int v = 1, int p = 0, int cc = 0)
{
    if (cat[v]) cc++;
    else cc = 0;

    //cout << "v=" << v << ",cc=" << cc << "\n";

    if (cc > m) return;

    if (p != 0 && adj[v].size() == 1) {
        cnt++;
        return;
    }

    for (auto w: adj[v]) {
        if (w == p) continue;
        trav(w, v, cc);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    cat.resize(n + 1, false);
    adj.resize(n + 1, vector<int>());

    for (int i = 1; i <= n; ++i) {
        char c;
        cin >> c;
        if (c == '1') {
            cat[i] = true;
        }
    }

    for (int i = 0; i < n-1; ++i) {
        int v, w;
        cin >> v >> w;
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    trav();
    cout << cnt << "\n";
}
