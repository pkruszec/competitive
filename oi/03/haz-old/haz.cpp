#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

int n;
vector<vector<int>> g;
vector<int> we, wy;

bool cond()
{
    if (we[1] != wy[1] - 1) return false;
    if (we[n] != wy[n] + 1) return false;

    for (int v = 2; v < n; ++v) {
        if (we[v] != wy[v]) return false;
    }

    return true;
}

vector<bool> vis;
void cycle(vector<int> &path, int v = 1, int p = 0)
{
    if (vis[v]) return;
    vis[v] = true;
    for (auto w: g[v]) {
        if (vis[w]) {
            if (w != p) {
                cout << "cycle ";
                for (auto x: path) {
                    cout << x << " ";
                }
                cout << "\n";
            }
            continue;
        }

        auto p1 = path;
        p1.push_back(w);
        cycle(path, w, v);
    }
}

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    g.resize(n+1, vector<int>());
    we.resize(n+1);
    wy.resize(n+1);
    vis.resize(n+1, false);

    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int x;
            cin >> x;
            g[i].push_back(x);
            we[x]++;
            wy[i]++;
        }
    }

    /*for (int i = 1; i <= n; ++i) {
        cout << i << " we=" << we[i] << " wy=" << wy[i] << "\n";
    }*/

    bool c = cond();

    if (c) {
        vector<int> path;
        cycle(path);
    }
}

//
// Graf skierowany
// Czy można dojść do jakiegoś V grafu, który już nie ma E, w taki sposób, że istnieją jeszcze E?
//

