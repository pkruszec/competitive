#include <iostream>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int n;
vector<pair<int, int>> E;
vector<int> in;
vector<int> out;

#if 0
vector<bool> vis;
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
#endif

vector<bool> vis1;
vector<int> path1;
int cv = 0;

bool ast(int v)
{
    bool result = true;
    cv ++;

    vis1[v] = true;

    int in = 0;
    int out = 0;

    for (auto &[f, t]: E) {
        if (f == v) {
            out++;
        }
        
        if (t == v) {
            // if (v == 2) {
            //     cout << "EDGE " << f << " " << t << "\n";
            // }
            in++;
        }

        if (!vis1[t]) {
            if (!ast(t)) {
                result = false;
                break;
            }
        }
    }

    if (result) {
        if (v == 1) {
            //cout << "---" << in << " != " << out-1 << "?\n";
            result =  in == out - 1;
        } else if (v == n) {
            result =  in == out + 1;
        } else {
            result = in == out;
        }
    }

    //cout << v << " [in=" << in << ", out=" << out << "] -> " << result << "\n";
    return result;
}

vector<bool> vis2;
void dfs(int v)
{
    vis2[v] = true;
    for (int i = 0; i < E.size(); ++i) {
        auto &[from, to] = E[i];
        if (from != v) continue;
        if (vis2[to]) continue;
        path1.push_back(to);
        dfs(to);
        return;
    }
}

vector<bool> vis3;
vector<int> pathres;
void dfs2(int v)
{
    // if (v == n) {
    //     pathres = path;
    //     return;
    // }

    for (int i = 0; i < E.size(); ++i) {
        if (vis3[i]) continue;

        auto &[from, to] = E[i];
        if (from != v) continue;

        vis3[i] = true;
        pathres.push_back(to);
        dfs2(to);
    }
}

bool check(int v, int p, int &fe)
{
    vis2[v] = true;
    for (int i = 0; i < E.size(); ++i) {
        auto &[from, to] = E[i];
        
        if (from != v) continue;
        if (to == n) continue;

        if (fe < 0) fe = i;

        if (to == p) {
            return true;
        }

        if (vis2[to]) continue;
        
        if (check(to, p, fe)) return true;
    }

    return false;
}

bool cycle()
{
    bool result = false;

    for (int i = 1; i < n; ++i) {
        path1.clear();
        for(int i = 0; i <= n; ++i){
            vis2[i] = false;
        }

        int fe = -1;
        if (check(i, i, fe)) {

            // for (auto x: path1) {
            //     cout << x << " ";
            // }
            // cout << "\n";

            E.erase(E.begin() + fe);

            // cout << fe << " <- FE\n";

            result = true;
            break;
        }
    }

    return result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

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

    in.resize(n+1, 0);
    out.resize(n+1, 0);
    vis1.resize(n+1, false);
    vis2.resize(n+1, false);
    vis3.resize(E.size(), false);

    for (auto &[f, t]: E) {
        in[f]++;
        out[t]++;
    }

    bool a = ast(1);

    if ((!a) || cv < n) {
        dfs(1);
        for (auto x: path1) {
            cout << x << " ";
        }
        cout << "0\n";
        return 0;
    }

    if (cycle()) {
        //cout << "CYCLE!\n";

        dfs2(1);
        for (auto x: pathres) {
            cout << x << " ";
        }
        cout << "0\n";

        return 0;
    }

    cout << "NIE\n";
    return 0;
}
