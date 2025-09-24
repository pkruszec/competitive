#include <iostream>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<pair<int, int>> E;
vector<bool> vis;
vector<int> path;
vector<int> vertices;

void dfs(int v)
{
    vertices.push_back(v);
    for (int i = 0; i < E.size(); ++i) {
        if (vis[i]) continue;
        auto &[from, to] = E[i];
        if (from != v) continue;
        path.push_back(i);
        vis[i] = true;
        dfs(to);
    }
}

/*
void run(int v, vector<bool> &vis, vector<int> &path, int vc=0)
{
    bool ok = false;

    for (int i = 0; i < E.size(); ++i) {
        if (vis[i]) continue;
        auto &[from, to] = E[i];
        if (from != v) continue;
        ok = true;

        auto vis2 = vis;
        vis2[i] = true;

        auto p = path;
        p.push_back(to);

        run(to, vis2, p, vc + 1);
    }

    if (!ok && vc < E.size()) {
        //cout << vc << " < " << E.size() << "\n";

        for (auto x : path) {
            cout << x << " ";
        }
        cout << "0\n";
        exit(0);
    }
}
*/



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int x;
            cin >> x;
            E.push_back({i, x});
        }
    }

    vis.resize(E.size(), false);

    // Find a path shorter than the total number of edges in the graph.

    // We start going an arbitrary path until we cannot.
    // Now we ask: are there any more edges?
    // If yes, we found the solution.
    // If no, check if we can eliminate some edges from the path.

    dfs(1);

    //cout << path.size() << " / " << E.size() << "\n";

    if (path.size() < E.size()) {
        // cout << "AAAAAA (" << path.size() << " | " << E.size() << ")\n";
        // return 0;

        for (int i = 1; i < vertices.size(); ++i) {
            cout << vertices[i] << " ";
        }
        cout << "0\n";
        return 0;
    }

    unordered_map<int, vector<int>> occ;
    
    for (int i = 0; i < vertices.size()-1; ++i) {
        occ[vertices[i]].push_back(i);
    }

// for (auto i: vertices) {
//         cout << i << " ";
//     }
//     cout << "\n";

    bool ok = false;
    for (auto [k, v] :occ) {
        if (v.size() >= 2) {
            int i = v[v.size() - 2];
            int j = v[v.size() - 1];
            if (1) {
                ok = true;
                vertices.erase(vertices.begin() + i, vertices.begin() + j);
                break;
            }
        }
    }

    // for (auto i: vertices) {
    //     cout << i << " ";
    // }
    // cout << "\n";

    // cout << "here\n";

    if (ok) {
        for (int i = 1; i < vertices.size(); ++i) {
            cout << vertices[i] << " ";
        }
        cout << "0\n";
        return 0;
    }

    // for (auto i: vertices) {
    //     cout << i << " ";
    // }
    // cout << "\n";

    // for (auto i: path) {
    //     cout << E[i].first << "->" << E[i].second << " ";
    // }
    // cout << "\n";

    // for (auto [k, v] :occ) {
    //     cout << k << ": ";
    //     for (auto x: v) {
    //         cout << x <<  " ";
    //     }
    //     cout<<"\n";
    // }

    cout << "NIE\n";

    // cout << "digraph {\n";
    // for (auto &[v, w]: E) {
    //     cout << "    " << v << " -> " << w << "\n";
    // }
    // cout << "}\n";

    return 0;
}
