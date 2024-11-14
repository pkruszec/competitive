#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

using Edges = vector<pair<int, int>>;
using Tmp = vector<pair<int, int>>;

struct Vertex {
    int level;
    int parent;
    int count;
    int children[2];
};

int k;
int match_count = 0;

Edges src_edges;
Edges dst_edges;
vector<Vertex> src_tree;
vector<Vertex> dst_tree;

//vector<bool> vis;
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

        if (vtx.count >= 2) {
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

#if 0
bool connected(vector<int> &src, Tmp &tmp, int i)
{
    if (i < 1) return true;

    auto current = tmp[i];
    auto potential_mutual = pair<int, int> {};
    auto potential_direct = tmp[i-1];

    bool mut = false;
    if (i >= 2) {
        potential_mutual = tmp[i-2];
        mut = (potential_mutual.second >= 2) && (src[i-2] >= 2);
    }

    bool current_mutual = false;

    for (auto [a, b]: dst_edges) {
        if (mut) {
            if (a == current.first && b == potential_mutual.first) current_mutual = true;
            if (b == current.first && a == potential_mutual.first) current_mutual = true;
        } else {
            if (a == current.first && b == potential_direct.first) return true;
            if (b == current.first && a == potential_direct.first) return true;
        }
    }

    for (auto [a, b]: dst_edges) {
        if (current_mutual) {
            if (a == potential_direct.first && b == potential_mutual.first) return true;
            if (b == potential_direct.first && a == potential_mutual.first) return true;
        }
    }

    // cout << "FALSE:" << i << "->" << (src[i-2]) << "\n";
    return false;
}

Tmp check_dim1(vector<int> &src, Tmp tmp, vector<Vertex> &tree, int fst_index, int n, int prev=0, int snd_index=0)
{
    auto rec = [&](int index){
        Vertex &v = tree[index];
        bool parent_valid = v.parent != 0 && v.parent != prev;
        bool fst_valid = v.count >= 1 && v.children[0] != prev;
        bool snd_valid = v.count >= 2 && v.children[1] != prev;
        int fst = v.children[0];
        int snd = v.children[1];

        if (fst_valid) {
            check_dim1(src, tmp, tree, fst, n, index);
        }
        if (snd_valid) {
            check_dim1(src, tmp, tree, snd, n, index);
        }
        if (parent_valid) {
            check_dim1(src, tmp, tree, v.parent, n, index);
        }

        if (fst_valid && snd_valid) {
            tmp=check_dim1(src, tmp, tree, fst, n, index, snd);
            check_dim1(src, tmp, tree, snd, n, index, fst);
        }

        if (fst_valid && parent_valid) {
            tmp=check_dim1(src, tmp, tree, fst, n, index, v.parent);
            check_dim1(src, tmp, tree, v.parent, n, index, fst);
        }

        if (snd_valid && parent_valid) {
            tmp=check_dim1(src, tmp, tree, snd, n, index, v.parent);
            check_dim1(src, tmp, tree, v.parent, n, index, snd);
        }
    };

    int fst_count = tree[fst_index].count + (tree[fst_index].parent != 0);
    int snd_count = tree[snd_index].count + (tree[snd_index].parent != 0);

    tmp.push_back(pair<int,int>(fst_index, tree[fst_index].count));
    if (fst_count < src[tmp.size() - 1]) return tmp;
    rec(fst_index);

    /*
    TODO: handle this

         O
        / \
       /   \
      O     O
     / \   / \
    O   O O   O
    */

    if (snd_index) {
        tmp.push_back(pair<int,int>(snd_index, tree[snd_index].count));
        if (snd_count < src[tmp.size() - 1]) return tmp;
        rec(snd_index);
    }

    if (tmp.size() == n) {
        bool eq = true;
        for (int i = 0; i < n; i += 1) {
            if (!connected(src, tmp, i)) {
                eq = false;
                break;
            }
        }
#if 0
        if (1) {
            for (auto x: tmp) {
                cout << x.first << " ";
            }
            cout << "\n";
        }
#endif
        if (eq) match_count = (match_count+1) % k;
        return tmp;
    }

    return tmp;
}
#endif

/*
int match(vector<bool> src_vis,vector<Vertex> &src_tree, vector<Vertex> &dst_tree, int src_index, int dst_index, int dst_prev=0)
{
    Vertex &src = src_tree[src_index];
    Vertex &dst = dst_tree[dst_index];

    // src_vis[src_index] = true;

    if (src.count == 0) {
        cout << "!\n";
        return 1;
    }


    if (dst.count == 0) return 0;

    if (src.count == 2) {
        int d0, d1;
        if (dst.parent == 0 || dst.parent == dst_prev) {
            if (dst.count != 2) return 0;
            d0 = dst.children[0];
            d1 = dst.children[1];
        } else {
            if (dst.count != 1) return 0;
            d0 = dst.parent;
            d1 = dst.children[0];
        }

        int m0 = match(src_tree, dst_tree, src.children[0], d0, dst_index);
        int m1 = match(src_tree, dst_tree, src.children[1], d1, dst_index);
        return m0 + m1;
    }

    if (src.count == 1) {
        int d0, d1 = 0;
        if (dst.parent == 0 || dst.parent == dst_prev) {
            if (dst.count < 1) return 0;
            d0 = dst.children[0];
            if (dst.count == 2) d1 = dst.children[1];
        } else {
            if (dst.count < 1) return 0;
            d0 = dst.parent;
            d1 = dst.children[0];
        }

        if (d1 == 0) return match(src_tree, dst_tree, src.children[0], d0, dst_index);
        int m0 = match(src_tree, dst_tree, src.children[0], d0, dst_index);
        int m1 = match(src_tree, dst_tree, src.children[1], d1, dst_index);
        return m0 + m1;
    }

    return 0;
}
*/

/*
IDEA: find all subgraphs of length n - their child counts, compare with src
each one of those is a 1-dim array
e.g.

   2
  / \
 1   0
 |
 0

2 1 0 0

first root, then lefts and rights

*/

int match(vector<Vertex> &src_tree, vector<Vertex> &dst_tree, int src_index, int dst_index)
{
    Vertex &src = src_tree[src_index];
    Vertex &dst = dst_tree[dst_index];
    
    if (dst.count < src.count) {
        // cout << "    " << dst_index << ": end" << "\n";
        return -1;
    }

    // int count = 0;

    if (src.count == 0) {
        return 1%k;
    }
    else if (src.count == 1 && dst.count == 1) {
        int v = match(src_tree, dst_tree, src.children[0], dst.children[0]);
        if (v < 0) return -1;

        return v;
        // if (v > count) count = v;
        // if (v < 1) count = 0;
    }
    else if (src.count == 1 && dst.count == 2) {
        int v0 = match(src_tree, dst_tree, src.children[0], dst.children[0]);
        int v1 = match(src_tree, dst_tree, src.children[0], dst.children[1]);
        if (v0 < 0 && v1 < 0) return -1;

        if (v0 < 0) return v1;
        if (v1 < 0) return v0;
        // int v = ((v0 > 0) ? v0 : 0) + ((v1 > 0) ? v1 : 0);
        // cout << dst_index << ":" << v << " x\n";

        int v = ((v0%k) + (v1%k)) % k;
        return v;
        // if (v > count) count = v;
        // if (v < 1) count = 0;
    }
    else if (src.count == 2 && dst.count == 2) {
        int v0 = -1;
        int v1 = -1;
        int v2 = -1;
        int v3 = -1;

        v0 = match(src_tree, dst_tree, src.children[0], dst.children[0]);
        if (v0 >= 0) v1 = match(src_tree, dst_tree, src.children[1], dst.children[1]);
        v2 = match(src_tree, dst_tree, src.children[0], dst.children[1]);
        if (v0 >= 0) v3 = match(src_tree, dst_tree, src.children[1], dst.children[0]);

        int vg0 = -1;
        int vg1 = -1;

        if (!(v0 < 0 || v1 < 0)) {
            vg0 = ((v0%k)*(v1%k)) % k;
        }

        if (!(v2 < 0 || v3 < 0)) {
            vg1 = ((v2%k)*(v3%k)) % k;
        }

        if (vg0 < 0 && vg1 < 0) return -1;
        if (vg0 < 0) vg0 = 0;
        if (vg1 < 0) vg1 = 0;

        int v = ((vg0%k) + (vg1%k)) % k;

        // cout << dst_index << "  " << v0 << ", "<< v1 << ", " << v2 << ", " << v3 << " -> " << v << "\n";

        // int v = min(v0, v1);
        // if (v > count) count = v;
        // if (v < 1) count = 0;
        return v;
    }

    // if (src_index == 1) {
    //     match_count = (match_count + 1 + two) % k;
    // }

    // cout << "   " << dst_index << ": " << count << "\n";

    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m >> k;

    src_tree.resize(n + 1, Vertex{});
    dst_tree.resize(m + 1, Vertex{});

    src_edges.resize(n - 1);
    dst_edges.resize(m - 1);

    for (int i = 0; i < n-1; ++i) {
        auto &p = src_edges[i];
        cin >> p.first >> p.second;
    }
    
    for (int i = 0; i < m-1; ++i) {
        auto &p = dst_edges[i];
        cin >> p.first >> p.second;
    }

    int max_src_level = 0;
    make_tree(src_tree, src_edges, 1, max_src_level);

    print_tree(src_tree, 1);

    for (int h = 1; h <= m; ++h) {
        for (int i = 0; i <= m; ++i) {
            dst_tree[i] = Vertex{};
        }

        int ignore;
        bool result = make_tree(dst_tree, dst_edges, h, ignore);
        if (!result) continue;

        print_tree(dst_tree, h);

        // int v = match(src_tree, dst_tree, 1, h);
        // cout << h << "." << i << " -> " << v << "\n"; 
        // if (v < 0) continue;
        // match_count = (match_count+v) % k;
        // match_count = ((match_count) + (v%k)) % k;


        for (int i = 1; i <= m; ++i) {
            if (dst_tree[i].level >= max_src_level) continue;

            int v = match(src_tree, dst_tree, 1, i);
            cout << h << "." << i << " -> " << v << "\n"; 
            if (v < 0) continue;
            // match_count = (match_count+v) % k;
            match_count = ((match_count) + (v%k)) % k;
        }

        // cout << "after " << h << ":" << match_count << "\n";
    }
    
    if (match_count % 2 != 0) {
        match_count = ((match_count) + 1) % k;
    }

    cout << match_count << "\n";

    return 0;
}

