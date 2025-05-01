#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

vector<int64_t> ex;
vector<int64_t> tree;

int64_t add(int64_t x, int64_t y) {
    return max(x, y) + 1;
}

int64_t compute(int l, int r) {
    vector<int64_t> op;
    for (int i = l; i <= r; ++i) {
        op.push_back(ex[i]);
    }

    while (op.size() >= 2) {
        int bi = 0;
        int64_t bv = INT_MAX;
        for (int i = 0; i < op.size() - 1; ++i) {
            int64_t v = max(op[i], op[i+1]);
            if (v < bv) {
                bv = v;
                bi = i;
            }
        }

        int64_t x = op[bi];
        int64_t y = op[bi+1];
        op.erase(op.begin() + bi);
        op.erase(op.begin() + bi);
        op.insert(op.begin() + bi, add(x, y));
    }

    return op[0];
}

void build(int v, int l, int r) {
    if (l == r) {
        tree[v] = add(ex[l], ex[l+1]);
        return;
    }

    int m = (l+r)/2;
    build(v*2+1, l, m);
    build(v*2+2, m+1, r);

    tree[v] = compute(l, r);
}

int64_t query(int l, int r, int v, int bl, int br) {
    cout << bl << " " << br << " -> " << tree[v] << "\n";
    if (bl == br) return 0 ;
    int bm = (bl+br)/2;
    query(0, 0, v*2+1, bl, bm);
    query(0, 0, v*2+2, bm+1, br);
    return 0;
    // if (l == bl && r == br) {
    //     return tree[v];
    // }

    // int m = (l+r)/2;
    // int bm = (bl+br)/2;

    // int64_t x = query(l, m, v*2+1, bl, bm);
    // int64_t y = query(m+1, r, v*2+2, bm+1, br);

    // return add(x, y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    ex.resize(n*2, 0);
    tree.resize(n*4, 0);

    for (int i = 0; i < n; ++i) {
        cin >> ex[i];
    }

    build(0, 0, ex.size() - 1);

    query(0,0, 0, 0, ex.size() - 1);
    return 0;

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << query(l, r, 0, 0, ex.size() - 1) << "\n";
    }

    return 0;
}