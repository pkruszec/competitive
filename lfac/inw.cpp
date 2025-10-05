#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n + 1, 0);
    vector<bool> vis(n + 1, false);
    
    vector<pair<int, int>> e;

    vector<vector<int>> ss;
    
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; ++i) {
        // TODO: Loop from i+1
        for (int j = 1; j <= n; ++j) {
            if ((i < j) && (a[i] > a[j])) {
                e.push_back({a[i], a[j]});
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (vis[i]) {
            continue;
        }

        vector<int> s;
        queue<int> q;

        q.push(i);
        vis[i] = true;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            s.push_back(v);

            for (auto [x, y]: e) {
                int w = 0;
                if (x == v) {
                    w = y;
                } else if (y == v) {
                    w = x;
                } else {
                    continue;
                }
                if (vis[w]) continue;

                vis[w] = true;
                q.push(w);
            }
        }

        sort(s.begin(), s.end());
        ss.push_back(s);
    }

    cout << ss.size() << "\n";
    for (auto &s: ss) {
        cout << s.size() << " ";
        for (auto x: s) {
            cout << x << " ";
        }
        cout << "\n";
    }
    
#if 0
    cout << "graph {\n";
    for (int i = 1; i <= n; ++i) {
        cout << i << ";\n";
    }
    
    for (auto [u, v]: e) {
        cout << u << " -- " << v << ";\n";
    }
    cout << "}\n";
#endif
    
    return 0;
}
