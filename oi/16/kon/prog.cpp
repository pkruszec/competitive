#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<vector<int>> xs(n - 1, vector<int>(n - 1, 0));
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < (n - 1) - i; ++j) {
            cin >> xs[i][j];
        }
    }

    vector<int> sc(n, 0);

    auto p = [&]() {
        for (auto x: sc) {
            cout << x << " ";
        }
        cout << "\n";
    };

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < (n - 1) - i; ++j) {
            for (int k = i; k < (i+j+1); ++k) {
                sc[k] += xs[i][j];

                // cout << "sc["<< k << "] += " << i << "," << (i+j+1) << " (" << xs[i][j] << ")\n";
            }

            cout << i+1 << "," << j+1 << ":   ";
            p();
        }
    }

    //p();

    vector<int> is(n, 0);
    for (int i = 0; i < n; ++i) {
        is[i] = i;
    }

    sort(is.begin(), is.end(), [&](auto a, auto b) -> bool {
        return sc[a] > sc[b];
    });

    for (auto x: is) {
        cout << x << " (" << sc[x] << ")\n";
    }

    vector<int> ans;
    for (int i = 0; i < k; ++i) {
        ans.push_back(is[i]);
    }

    sort(ans.begin(), ans.end());

    for (auto x: ans) {
        cout << x + 1 << " ";
    }
    cout << "\n";

    return 0;
}
