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
    int children[3];
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

bool make_tree(vector<Vertex> &tree, Edges &edges, int idx, int &max_level, int prev=0)
{
    Vertex &vtx = tree[idx];
    vtx.parent = prev;
    vtx.level = tree[vtx.parent].level + 1;
    if (vtx.level > max_level) max_level = vtx.level;

    for (auto &edge: edges) {
        int other;
        if (edge.first == idx) {
            other = edge.second;
        } else if (edge.second == idx) {
            other = edge.first;
        } else continue;
        if (other == prev) continue;

#if 0
        cout << idx << "->" << other << "\n";
        if (vtx.count >= 2) {
            cout << other << "  " << vtx.parent << " -> " << idx << " (" << vtx.children[0] << ", " << vtx.children[1] << ")\n";
            assert(false);
        }
#endif

        if (vtx.count >= 3) {
            return false;
        }

        vtx.children[vtx.count++] = other;
        if (!make_tree(tree, edges, other, max_level, idx)) return false;
    }

    return true;
}

void print_tree(vector<Vertex> &tree, int idx, int indent=0)
{
    auto &vtx = tree[idx];

    for (int i = 0; i < indent; ++i) cout << " ";

    cout << idx << " (" << vtx.level << ")\n";
    // cout << idx << "\n";

    for (int i = 0; i < vtx.count; ++i) {
        print_tree(tree, vtx.children[i], indent + 2);
    }
}

void make_src(vector<int> &src, vector<Vertex> &tree, int index)
{
    Vertex &v = tree[index];
    // src.push_back(v.count + (v.parent != 0));
    src.push_back(v.count);

    for (int i = 0; i < v.count; ++i) {
        make_src(src, tree, v.children[i]);
    }
}

void make_ends(vector<pair<int, int>> &ends, vector<Vertex> &tree, int index, int max_level=INT_MAX, int mult=0)
{
    auto &vtx = tree[index];

    if (vtx.count == 0 || vtx.level >= max_level) {
        ends.push_back({vtx.level, mult});
    }

    if (vtx.level >= max_level) return;
    for (int i = 0; i < vtx.count; ++i) {
        make_ends(ends, tree, vtx.children[i], max_level, mult + (vtx.count >= 2));
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int match_count = 0;
    int k;
    int n, m;
    cin >> n >> m >> k;

    Edges src_edges;
    Edges dst_edges;
    vector<Vertex> src_tree;
    vector<Vertex> dst_tree;

    src_edges.resize(n - 1);
    src_tree.resize(n + 1, Vertex{});
    dst_edges.resize(m - 1);
    dst_tree.resize(m + 1, Vertex{});
    
    for (int i = 0; i < n-1; ++i) {
        auto &p = src_edges[i];
        cin >> p.first >> p.second;
    }
    
    for (int i = 0; i < m-1; ++i) {
        auto &p = dst_edges[i];
        cin >> p.first >> p.second;
    }

    int max_src_level = 0;
    vector<pair<int, int>> src_ends;
    vector<pair<int, int>> dst_ends;
    make_tree(src_tree, src_edges, 1, max_src_level);
    make_ends(src_ends, src_tree, 1);
    // print_tree(src_tree, 1);

    cout << "S" << " :: ";
    for (auto x: src_ends) {
        cout << x.first << "(" << x.second << ")" << " ";
    }cout << "\n";

    for (int first = 1; first <= m; ++first) {
        int max_dst_level = 0;
        for (auto &x: dst_tree) x = {};
        make_tree(dst_tree, dst_edges, first, max_dst_level);
        if (max_dst_level < max_src_level) continue;
        // print_tree(dst_tree, first);
        dst_ends.clear();
        make_ends(dst_ends, dst_tree, first, max_src_level);

        cout << first << " :: ";
        for (auto x: dst_ends) {
            cout << x.first << "(" << x.second << ")" << " ";
        }cout << "\n";
    }

    #if 0
    queue<Path> paths;

    for (int first = 1; first <= m; ++first) {
        paths.push(Path {first, 0, 1});

        while (!paths.empty()) {
            Path path = paths.front();
            paths.pop();

            vector<int> &adj = dst[path.v];
            Vertex &src = src_tree[path.s];

            int child_count = adj.size() - (path.p != 0);
            int sc = src.count + (src.parent != 0);

            if (child_count < sc) {
                continue;
            }

            if (child_count == 0 && src.count == 0) {
                match_count = (match_count+1) % k;
            }

            int c[3] = {};
            int cc = 0;
            for (int i = 0; i < adj.size(); ++i) {
                int x = adj[i];
                if (x == path.p) continue;
                c[cc++] = x;
            }

            assert(cc == child_count);

            if (sc == 1) {
                for (int i = 0; i < cc; ++i) {
                    paths.push(Path {c[i], path.v, src.children[0]});
                }
            }
            else if (src.count == 2) {
                if (cc == 2) {
                    // cout << path.p << " -> "<< path.v << "\n";
                    paths.push(Path {c[0], path.v, src.children[0]});
                    paths.push(Path {c[1], path.v, src.children[1]});
                } else if (cc == 3) {
                    assert(false);
                    // paths.push(Path {c[0], path.v, src.children[0]});
                    // paths.push(Path {c[0], path.v, src.children[1]});
                    // paths.push(Path {c[1], path.v, src.children[0]});
                    // paths.push(Path {c[1], path.v, src.children[1]});
                    // paths.push(Path {c[2], path.v, src.children[0]});
                    // paths.push(Path {c[2], path.v, src.children[1]});
                }
            }
        }

        #if 0
        for (int j = 0; j < dst[i].size(); ++j) {
            bool &b = vis[i].v[j];
            if (b) continue;
            b = true;

            int v = dst[i][j];
            // cout << i << " -> " << v << "\n";

        }
        #endif
    }

    if (match_count % 2 != 0) {
        match_count = (match_count+1) % k;
    }
    #endif

    cout << match_count << "\n";

    return 0;
}
