#include <iostream>
#include <vector>
using namespace std;

struct S {
    bool zero;
    int l, r, z;
};

vector<S> tree;

S merge(S &a, S &b) {
    S s = {};
    s.zero = a.zero&&b.zero;
    if (a.zero) {
        s.l = a.l + b.l;
    } else {
        s.l = a.l;
    }

    if (b.zero) {
        s.r = a.r + b.r;
    } else {
        s.r = b.r;
    }

    s.z = max(max(a.z, b.z), a.r+b.l);
    return s;
}

void build(vector<bool> &s, int v, int l, int r) {
    if (l==r) {
        if (s[l]) {
            tree[v] = S{false, 0, 0, 0};
        } else {
            tree[v] = S{true, 1, 1, 1};
        }
        return;
    }

    int m = (l+r)/2;
    build(s, v*2 + 1, l, m);
    build(s, v*2 + 2, m+1, r);
    tree[v] = merge(tree[v*2+1], tree[v*2+2]);
}

void update(int v, int l, int r, int p, int x) {
    if (l==r) {
        if (x) {
            tree[v] = S{false, 0, 0, 0};
        } else {
            tree[v] = S{true, 1, 1, 1};
        }
        return;
    }
    
    int m = (l+r)/2;
    if (p<=m) {
        update(v*2+1, l, m, p, x);
    } else {
        update(v*2+2, m+1, r, p, x);
    }

    tree[v] = merge(tree[v*2+1], tree[v*2+2]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;
    
    vector<bool> s(n);
    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;
        s[i] = (c == '1');
    }

    tree.resize(n*4);
    build(s, 0, 0, n-1);
    
    for (int z = 0; z < q; ++z) {
        int x;
        cin >> x;
        x--; 
        s[x] = !s[x];
        update(0, 0, n-1, x, s[x]);
        cout << tree[0].z << "\n";
    }
    
    return 0;
}

