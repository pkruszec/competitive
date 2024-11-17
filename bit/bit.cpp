#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <assert.h>
#include <limits.h>

using namespace std;

using Edges = vector<pair<int, int>>;

struct Vertex {
    int level;
    int parent;
    int count;
    int children[2];
};

struct Vis {
    bool v[3];
};

struct Path {
    int v;
    int p;
    int s;
    // bool dbl;
    // int n[2];
};

bool make_tree(vector<Vertex> &tree, Edges &edges, int idx, int prev=0)
{
    Vertex &vtx = tree[idx];
    vtx.parent = prev;
    vtx.level = tree[vtx.parent].level + 1;

    for (auto &edge: edges) {
        int other;
        if (edge.first == idx) {
            other = edge.second;
        } else if (edge.second == idx) {
            other = edge.first;
        } else continue;
        if (other == prev) continue;

        if (vtx.count >= 2) {
            return false;
        }

        vtx.children[vtx.count++] = other;
        if (!make_tree(tree, edges, other, idx)) return false;
    }

    return true;
}

void print_tree(vector<Vertex> &tree, int idx, int indent=0)
{
    auto &vtx = tree[idx];

    for (int i = 0; i < indent; ++i) cout << " ";

    // cout << idx << " (" << vtx.level << ")\n";
    cout << idx << "\n";

    for (int i = 0; i < vtx.count; ++i) {
        print_tree(tree, vtx.children[i], indent + 2);
    }
}

void print_visited(vector<vector<bool>> &visited)
{
    int bb = visited.size()-1;

    cout << "+>";
    for (int i = 1; i <= bb; ++i) cout << i;
    cout << "\n|\n";
    for (int i = 1; i <= bb; ++i) {
        cout << i << " ";
        for (int j = 1; j <= bb; ++j) {
            if (i == j) {
                cout << "-";
            } else {
                cout << visited[i][j];
            }
        }
        cout << "\n";
    }
}

int find_all(vector<vector<int>> &adj, vector<vector<bool>> &visited, vector<Vertex> &tree, vector<vector<int>> &paths,
             vector<int> path, int d, int s, int p=0)
{
    vector<int> &a = adj[d];
    Vertex &v = tree[s];

    int c[3];
    int cc = 0;
    for (auto x: a) {
        if (x != p) c[cc++] = x;
    }

    if (cc < v.count) return 0;
    path.push_back(d);


    /*
    if (p != 0 && !visited[p][d] && !visited[d][p]) {
        found_new = true;
        visited[p][d] = true;
        visited[d][p] = true;
    }
    */

    if (v.count == 0) {
        /*
        if (0){
            cout << p << " -> " << d << "\n";
            print_visited(visited);
            cout << "\n";
        }
        */

        for (auto &p: paths) {
            bool eq = true;
            bool eq_rev = true;
            for (int i = 0; i < p.size(); ++i) {
                if (path[i] != p[i]) {
                    eq = false;
                    break;
                }
            }
            if (eq) return 0;

            for (int i = 0; i < p.size(); ++i) {
                if (path[i] != p[p.size() - 1 - i]) {
                    eq_rev = false;
                    break;
                }
            }
            if (eq_rev) return 0;
        }

        // for (auto x: path) {
        //     cout << x << " ";
        // }
        // cout << "\n";

        paths.push_back(path);

        return 1;
    }


    if (v.count == 1) {
        int sm = 0;
        for (int i = 0; i < cc; ++i) {
            sm += find_all(adj, visited, tree, paths, path, c[i], v.children[0], d);
        }
        return sm;
    }

    if (cc == 2 && v.count == 2) {
        path.push_back(c[1]);
        int a = find_all(adj, visited, tree, paths, path, c[0], v.children[0], d);
        path.pop_back();

        path.push_back(c[0]);
        int b = find_all(adj, visited, tree, paths, path, c[1], v.children[1], d);
        path.pop_back();

        path.push_back(c[0]);
        int x = find_all(adj, visited, tree, paths, path, c[1], v.children[0], d);
        path.pop_back();

        path.push_back(c[1]);
        int y = find_all(adj, visited, tree, paths, path, c[0], v.children[1], d);
        path.pop_back();

        return a*b + x*y;
    }

    if (cc == 3 && v.count == 2) {
        path.push_back(c[1]);
        int a = find_all(adj, visited, tree, paths, path, c[0], v.children[0], d);
        path.pop_back();

        path.push_back(c[0]);
        int b = find_all(adj, visited, tree, paths, path, c[1], v.children[1], d);
        path.pop_back();

        path.push_back(c[2]);
        int x = find_all(adj, visited, tree, paths, path, c[0], v.children[0], d);
        path.pop_back();

        path.push_back(c[0]);
        int y = find_all(adj, visited, tree, paths, path, c[2], v.children[1], d);
        path.pop_back();

        path.push_back(c[2]);
        int e = find_all(adj, visited, tree, paths, path, c[1], v.children[0], d);
        path.pop_back();

        path.push_back(c[1]);
        int f = find_all(adj, visited, tree, paths, path, c[2], v.children[1], d);
        path.pop_back();

        path.push_back(c[0]);
        int g = find_all(adj, visited, tree, paths, path, c[1], v.children[0], d);
        path.pop_back();

        path.push_back(c[1]);
        int h = find_all(adj, visited, tree, paths, path, c[0], v.children[1], d);
        path.pop_back();

        path.push_back(c[0]);
        int i = find_all(adj, visited, tree, paths, path, c[2], v.children[0], d);
        path.pop_back();

        path.push_back(c[2]);
        int j = find_all(adj, visited, tree, paths, path, c[0], v.children[1], d);
        path.pop_back();

        path.push_back(c[1]);
        int k = find_all(adj, visited, tree, paths, path, c[2], v.children[0], d);
        path.pop_back();

        path.push_back(c[2]);
        int l = find_all(adj, visited, tree, paths, path, c[1], v.children[1], d);
        path.pop_back();

        return a*b + x*y + e*f + g*h + i*j + k*l;
    }

    return 0;
}

int find_rec(vector<Vertex> &tree, int s)
{
    Vertex &v = tree[s];
    if (v.count == 0) {
        return 1;
    }
    if (v.count == 1) {
        return find_rec(tree, v.children[0]);
    }

    if (v.count == 2) {
        int a = find_rec(tree, v.children[0]);
        int b = find_rec(tree, v.children[1]);
        int s = a*b * (a==b ? 2 : 1);
        return s;
    }

    return 0;
}

int best_src(vector<int> &nbors)
{
    int src = 1;
    int nc = 0;
    for (int i = 1; i < nbors.size(); ++i) {
        if (nbors[i] > nc) {
            nc = nbors[i];
            src = i;
        }
    }

    return src;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int k;
    int n, m;
    cin >> n >> m >> k;

    Edges src_edges;
    Edges dst_edges;
    vector<Vertex> src_tree;

    vector<int> nbors(n+1, 0);

    vector<vector<int>> adj(m+1, vector<int>());
    vector<vector<bool>> visited(m+1, vector<bool>(m+1, false));

    src_edges.resize(n - 1);
    src_tree.resize(n + 1, Vertex{});
    dst_edges.resize(m - 1);
    
    for (int i = 0; i < n-1; ++i) {
        auto &p = src_edges[i];
        cin >> p.first >> p.second;

        nbors[p.first]++;
        nbors[p.second]++;
    }
    
    for (int i = 0; i < m-1; ++i) {
        auto &p = dst_edges[i];
        cin >> p.first >> p.second;

        adj[p.first].push_back(p.second);
        adj[p.second].push_back(p.first);
    }

    int src = best_src(nbors);
    while (!make_tree(src_tree, src_edges, src)) {
        for (auto &x: src_tree) x = Vertex{};
        nbors[src]=-1;
        src=best_src(nbors);
    }
    // print_tree(src_tree, src);

    vector<vector<int>> paths;

    int f = 0;
    for (int i = 1; i <= m; ++i) {
        f += find_all(adj, visited, src_tree, paths, vector<int>(), i, src);
    }

    int r = find_rec(src_tree, src);

    cout << (f*r) % k << "\n";
    // cout << f << "\n";
    // cout << r << "\n";

    return 0;
}
