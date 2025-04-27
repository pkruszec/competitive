#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

vector<int64_t> ex;

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

int64_t query(int l, int r) {
    return compute(l, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    ex.resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> ex[i];
    }

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << query(l, r) << "\n";
    }

    return 0;
}