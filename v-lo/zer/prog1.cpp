#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;
    vector<bool> s(n);
    vector<int> l(n, 0);
    vector<int> r(n, 0);
    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;
        s[i] = c=='1';
    }

    auto comp_l = [&](int i) {
        int L = 0;
        for (int k = i; k < n; ++k) {
            if (s[k]) break;
            L++;
        }
        l[i] = L;
    };

    auto comp_r = [&](int i) {
        int R = 0;
        for (int k = n-1; k >= i; --k) {
            if (s[k]) break;
            R++;
        }
        r[i] = R;
    };

    for (int i = 0; i < n; ++i) {
        comp_l(i);
        comp_r(i);
    }

    for (int z = 0; z < q; ++z) {
        int x;
        cin >> x;
        x--;
        s[x] = !s[x];
        for (int i = 0; i <= x; ++i) {
            comp_l(i);
        }
        for (int i = x; i >= 0; --i) {
            comp_r(i);
        }
        int m = 0;
        for (int i = 0; i < n; ++i) {
            m = max(m, l[i]);
            m = max(m, r[i]);
        }
        cout << m << "\n";
    }

    return 0;
}

