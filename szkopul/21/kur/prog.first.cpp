#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int d;
};

int n, m;
vector<int> k;
vector<Node> t;

Node merge(int v, int l, int r) {
    int s = (l+r)/2;
    int lc = s-l+1;
    int rc = r-(s+1)+1;
    int le = v*2+1;
    int re = v*2+2;

    if (l==r) {
        return Node{k[l]};
    }

    if (t[le].d == 0) {
        int ld = le*2+1;
        int rd = le*2+2;

        if (t[ld].d == t[re].d || t[rd].d == t[re].d) {
            return t[re];
        }
    }

    if (t[re].d == 0) {
        int ld = re*2+1;
        int rd = re*2+2;

        if (t[rd].d == t[le].d || t[rd].d == t[le].d) {
            return t[le];
        }
    }

    if (lc < rc) {
        return t[re];
    }
    if (lc > rc) {
        return t[le];
    }

    if (t[le].d == t[re].d) {
        return t[le];
    }

/*
    if (t[le].d == 0) {
        int ld = le*2+1;
        int rd = le*2+2;

        if (t[ld].d == t[re].d || t[rd].d == t[re].d) {
            return t[re];
        }
    }

    if (t[re].d == 0) {
        int ld = re*2+1;
        int rd = re*2+2;

        if (t[rd].d == t[le].d || t[rd].d == t[le].d) {
            return t[le];
        }
    }
    */

    return Node{0};
}

void build(int v, int l, int r) {
    if (l==r) {
        t[v] = Node{k[l]};
        return;
    }
    
    int s = (l+r)/2;
    int lc = s-l+1;
    int rc = r-(s+1)+1;
    
    int le = v*2+1;
    int re = v*2+2;
    build(le, l, s);
    build(re, s+1, r);

    t[v] = merge(v, l, r);

    //cout << l << " " << r << ": " << s << ", " << lc << ", " << rc << "\n";
    /*
    if (lc == rc) {
        if (t[re].d == t[le].d) {
            t[v] = t[le];
        }
    } else if (lc == rc) {

    } else if (lc < rc) {
        t[v] = t[re];
    } else if (lc > rc) {
        t[v] = t[le];
    } else {
        t[v] = Node{0};
    }
    */

}

int query(int l, int r, int v=0, int l=0, int r=n-1) {

    int s=(l+r)/2;
    query();
    return -1;
}

#if 1
void print(int v=0, int i=0) {
    if (v >= t.size()) {
        return;
    }
    print(v*2 + 2, i+2);
    for (int j=0; j<i; ++j) cout << " ";
    cout << t[v].d << "\n";
    print(v*2 + 1, i+2);
}
#endif

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    k.resize(n);
    t.resize(2*n, {});
    for (int i = 0; i < n; ++i) {
        cin >> k[i];
    }

    build(0, 0, n-1);
    print();

    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << query(l, r) << "\n";
    }

    return 0;
}

