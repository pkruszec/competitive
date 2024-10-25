#include <iostream>
#include <vector>

using namespace std;

int k;

struct Vertex {
    int parent;
    int count;
    int children[2];
};

using Edges = vector<pair<int, int>>;

void make_tree(vector<Vertex> &tree, Edges &edges, int idx, int prev=0)
{
    Vertex &vtx = tree[idx];
    vtx.parent = prev;

    for (auto &edge: edges) {
        int other;
        if (edge.first == idx) {
            other = edge.second;
        } else if (edge.second == idx) {
            other = edge.first;
        } else continue;
        if (other == prev) continue;

        vtx.children[vtx.count++] = other;
        make_tree(tree, edges, other, idx);
    }
}

void print_tree(vector<Vertex> &tree, int idx, int indent=0)
{
    auto &vtx = tree[idx];

    for (int i = 0; i < indent; ++i) cout << " ";
    cout << idx << "\n";

    for (int i = 0; i < vtx.count; ++i) {
        print_tree(tree, vtx.children[i], indent + 2);
    }
}

// TODO: should we mod k here too?
int match(vector<Vertex> &src_tree, vector<Vertex> &dst_tree, int src_index, int dst_index, int dst_prev=0)
{
    int match_count = 0;

    Vertex &src = src_tree[src_index];
    Vertex &dst = dst_tree[dst_index];

    if (src.count == 0) return 1;

    // cout << "  " << dst_index;
    // if (src.count == 0) {
    //     match_count++;
    //     cout << "!";
    // }
    // cout << "\n";

    for (int i = 0; i < src.count; ++i) {
        int src_child_index = src.children[i];
        // Vertex &src_child = src_tree[src_child_index];

        if (dst.parent != 0 && dst.parent != dst_prev) {
            match_count += match(src_tree, dst_tree, src_child_index, dst.parent, dst_index);
        }

        for (int j = 0; j < dst.count; ++j) {
            if (dst.children[j] == dst_prev) continue;
            match_count += match(src_tree, dst_tree, src_child_index, dst.children[j], dst_index);
        }
    }

    return match_count;
}

/*
void match(int source_node, int selected)
{
    for (int i = 1; i <= n-1; ++i) {
        auto [a, b] = np[i];
        int other;
        if (a == source_node) {
            other = b;
        } else if (b == source_node) {
            other = a;
        } else {
            continue;
        }

        if (nvis[i]) continue;
        nvis[i] = true;



    }

    cout << selected << "\n";
}
void dfs(int v)
{
    vis[v] = true;
    for (auto &p: mp) {
        auto [u, w] = p;
        int o = 0;
        if (u == v) {
            o = w;
        } else if (u == w) {
            o = v;
        } else continue;

        if (visited[o]) continue;
        visited[o] = true;


    }
}
*/

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m >> k;

    Edges src_edges;
    Edges dst_edges;
    vector<Vertex> src_tree;
    vector<Vertex> dst_tree;

    src_tree.resize(n + 1, Vertex{});
    dst_tree.resize(m + 1, Vertex{});

    src_edges.resize(m - 1);
    dst_edges.resize(m - 1);

    for (int i = 0; i < n-1; ++i) {
        auto &p = src_edges[i];
        cin >> p.first >> p.second;
    }
    
    for (int i = 0; i < m-1; ++i) {
        auto &p = dst_edges[i];
        cin >> p.first >> p.second;
    }

    make_tree(src_tree, src_edges, 1);
    make_tree(dst_tree, dst_edges, 1);

    // print_tree(src_tree, 1);
    // print_tree(dst_tree, 1);

    int match_count = 0;
    for (int i = 1; i <= m; ++i) {
        // cout << "match\n";
        match_count = (match_count % k + match(src_tree, dst_tree, 1, i) % k) % k;
    }
    cout << match_count << "\n";

    /*
        notes:
        - number of edges for each node <= 3
        - for match, must be connected        
    */

    // for (int j = 1; j <= m; ++j) {
    //     for (int i = 1; i <= n; ++i) nvis[i] = false;
    // }


    // match(1, 2);

    return 0;
}
