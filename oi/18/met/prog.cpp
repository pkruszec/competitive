#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;

    vector<int> p(n + 1, 0);
    vector<int> o(m + 1, 0);

    for (int i = 1; i <= m; ++i) {
        cin >> o[i];
    }

    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }

    vector<int> c(n + 1, 0);
    vector<int> d(n + 1, -1);

    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int l, r, a;
        cin >> l >> r >> a;

        if (l <= r) {
            for (int j = l; j <= r; ++j) {
                c[o[j]] += a;
                if (d[o[j]] < 0 && c[o[j]] >= p[o[j]]) {
                    d[o[j]] = i+1;
                }
            }
        } else {
            for (int j = l; j <= m; ++j) {
                c[o[j]] += a;
                if (d[o[j]] < 0 && c[o[j]] >= p[o[j]]) {
                    d[o[j]] = i+1;
                }
            }
            for (int j = 1; j <= r; ++j) {
                c[o[j]] += a;
                if (d[o[j]] < 0 && c[o[j]] >= p[o[j]]) {
                    d[o[j]] = i+1;
                }
            }
        }

    }

    for (int i = 1; i <= n; ++i) {
        if (d[i] >= 0) {
            cout << d[i] << "\n";
        } else {
            cout << "NIE\n";
        }
    }

    return 0;
}
