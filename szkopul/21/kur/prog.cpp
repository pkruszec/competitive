#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Node {
    int v;
    int k;
};

int n, m;
vector<int> p;
unordered_map<int, unordered_map<int, Node>> tree;

Node compute(int l, int r) {
    unordered_map<int, int> h;
    for (int k = l; k <= r; ++k) h[p[k]]++;
    for (auto [k, v]: h) {
        if (v*2 > (r-l+1)) return Node{k, v};
    }
    return Node{0, 0};

    /*
    vector<int> c;
    for (int k = l; k <= r; ++k) c.push_back(p[k]);
    sort(c.begin(), c.end());

    Node n = {};
    for (auto x: c) {
        if (n.k == 0) {
            n.k = 1;
            n.v = x;
        } else {
            if (n.v != x) {
                n.k--;
            } else {
                n.k++;
            }
        }
    }
    return n;
    */
}

Node query(int l, int r) {
    if (tree[l].find(r) != tree[l].end()) {
        return tree[l][r];
    }

    Node c = compute(l, r);

    return c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        auto n = query(l, r);
        //cout << l << "," << r << "->" << n.v << "\n";
        cout << (n.k>0 ? n.v : 0) << "\n";
    }

    return 0;
}

