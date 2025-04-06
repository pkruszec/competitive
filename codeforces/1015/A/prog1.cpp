#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

vector<bool> printed;

void perm(int n, int k, vector<vector<int>> &xs, int i, vector<int> v)
{
    if (printed[n]) return;
    if (i > k && v.size() == k) {
        for (auto x: v) {
            cout << x << " ";
        }
        cout << "\n";
        printed[n] = true;
        return;
    }

    for (auto x: xs[i]) {
        if (x > v[v.size() - 1] && find(v.begin(), v.end(), x) == v.end()) {
            v.push_back(x);
            perm(n, k, xs, i+1, v);
            v.pop_back();
        }
    }
}

int main()
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);

    int n;
    cin >> n;
    printed.resize(n);

    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;

        vector<vector<int>> xs(k+1);
        int c = 0;

        for (int j = 2; j <= k; ++j) {
            for (int x = 0;; x++) {
                int n = j*x + j-1;
                if (n > k) break;
                xs[j].push_back(n);
                c++;
            }
        }

        if (c < k) {
            cout << "-1\n";
            continue;
        }

        // for (int j = 2; j <= k; ++j) {
        //     cout << "( ";
        //     for (auto x: xs[j]) {
        //         cout << x << " ";
        //     }
        //     cout << ") ";
        // }
        // cout << "\n";

        for (auto x: xs[2]) {
            for (auto y: xs[2]) {
                if (x==y) continue;
                perm(i, k, xs, 3, {x, y});
                if (printed[i]) goto next;
                //cout << "    " << x << " " << y << "\n";
            }
        }

        cout << "-1\n";
        next:;
    }
    return 0;
}
