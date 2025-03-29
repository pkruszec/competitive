#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> tree;
int base = 1;
int n;

const int INF = 1e9 + 7;

void init(vector<int>& a) {
    n = a.size();
    while (base < n)
        base *= 2;
    tree.resize(2 * base, INF);

    for (int i = 0; i < n; i++)
        tree[i + base] = a[i];
    for (int i = base - 1; i > 0; i--)
        tree[i] = min(tree[2 * i], tree[2 * i + 1]);
}

int query(int a, int b, int i = 1, int ia = 0, int ib = -1) {
    if (ib == -1) ib = base - 1;
    
    if (b < ia || a > ib)
        return INF;
    if (a <= ia && ib <= b)
        return tree[i];
    int s = (ia + ib) / 2;
    int l = query(a, b, 2 * i, ia, s);
    int r = query(a, b, 2 * i + 1, s + 1, ib);
    return min(l, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    init(A);

    int m;
    cin >> m;

    for (int i = 0; i < m; ++i) {
        int p, k;
        cin >> p >> k;
        cout << query(p - 1, k - 1) << "\n";
    }

    return 0;
}
