#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int n;
vector<int> tx;
vector<vector<int>> ta;
vector<vector<int>> td;
vector<int> ts;
vector<int> md;
vector<int> mp;

bool topo()
{
    vector<int> indeg(n+1, -1);
    for (int v = 1; v <= n; ++v) {
        indeg[v] = td[v].size();
    }

    for (int v = 1; v <= n; ++v) {
        if (indeg[v] == 0) {
            ts.push_back(v);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (i >= ts.size()) return false;
        int v = ts[i];
        for (auto u: ta[v]) {
            indeg[u]--;
            if (indeg[u] <= 0) {
                ts.push_back(u);
            }
        }
    }

    return true;
}

int time()
{
    int ms = 0;
    for (int i = 0; i < n; ++i) {
        int v = ts[i];
        md[v] = 0;
        for (auto u: td[v]) {
            md[v] = max(md[v], md[u]);
        }
        md[v] += tx[v];
        ms = max(ms, md[v]);
    }
    for (int i = n-1; i >= 0; --i) {
        int v = ts[i];
        mp[v] = 0;
        for (auto u: ta[v]) {
            mp[v] = max(mp[v], mp[u] + tx[u]);
        }
    }

    return ms;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    tx.resize(n+1);
    ta.resize(n+1);
    td.resize(n+1);
    md.resize(n+1);
    mp.resize(n+1);

    for (int i = 1; i <= n; ++i) {
        int t, k;
        cin >> t >> k;

        tx[i] = t;
        for (int j = 1; j <= k; ++j) {
            int b;
            cin >> b;
            ta[b].push_back(i);
            td[i].push_back(b);
        }
    }

    if (!topo()) {
        cout << "CYKL\n";
        return 0;
    }

    int ms = time();
    cout << ms << "\n";

    int q;
    cin >> q;
    while (q--) {
        int c, t;
        cin >> c >> t;
        if (t > ms - md[c] - mp[c]) {
            cout << "TAK\n";
        } else {
            cout << "NIE\n";
        }
    }

    return 0;
}

/*__________________
    4 1_     
    4   5
    4   5
    4   5
    4_  5_
          3 6
          3 6_
          3   2_
          3
          3_


    4 1 5
    3 6 2

    a b_
    a   c
    a   c
    a_  c
        c
        c_
*/
