#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

vector<pair<int, int>> e;

void dfs(int v, unordered_set<int> &ev, vector<int> &path, int ec)
{
    bool found = false;
    for (int i = 0; i < (int)e.size(); ++i) {
        if (ev.count(i)) continue;
        auto &[c, w] = e[i];

        if (c != v) continue;
        found = true;

        //cout << v << "->" << w << "\n";

        auto ev1 = ev;
        auto path1 = path;

        ev1.insert(i);
        path1.push_back(w);
        dfs(w, ev1, path1, ec - 1);
    }
    
    if (ec > 0 && !found) {
        for (auto x: path) {
            cout << x << " ";
        }
        cout << "0\n";
        exit(0);
    }
}

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int x;
            cin >> x;
            e.push_back({i, x});
        }
    }
    
    unordered_set<int> ev;
    vector<int> path;
    dfs(1, ev, path, e.size());

    cout << "NIE\n";
    return 0;
}

//
// Graf skierowany
// Czy można dojść do jakiegoś V grafu, który już nie ma E, w taki sposób, że istnieją jeszcze E?
//

