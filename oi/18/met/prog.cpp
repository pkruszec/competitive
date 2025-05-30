#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void update(int l, int r, int a)
{
}

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

    vector<int> ans(n+1, -1);

    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int l,r,a;
        cin >> l >> r >> a;

        if (l <= r) {
            update(l, r, a);
        } else {
            update(l, m, a);
            update(1, r, a);
        }

        for (int j = 1; j <= m; ++j) {
            query(j);
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (ans[i] < 0) {
            cout << "NIE\n";
        } else {
            cout << ans[i] << "\n";
        }
    }

    return 0;
}
