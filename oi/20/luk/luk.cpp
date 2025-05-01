#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

vector<vector<int>> adj;
//vector<int> dp;

// vector<vector<int>> tree;
// vector<int> parent;

// void mktree(int v, int o = 0)
// {
//     parent[v] = o;
//     for (auto w: adj[v]) {
//         if (w == o) continue;
//         tree[v].push_back(w);
//         mktree(w, v);
//     }
// }

// void cf(int v, int o = 0)
// {
//     // dp[v] = 0;
//     for (auto w: adj[v]) {
//         if (w == o) continue;
//         dp[v]++;
//         cf(w, v);
//     }
// }

int sp(int v, int k, int o)
{
    int r = 0;
    for (auto w: adj[v]) {
        if (w == o) continue;
        r += sp(w, k, v) + 1;
    }
    return max(0, r - k);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    if (n == 1) {
        cout << "0\n";
        return 0;
    }

    adj.resize(n + 1, vector<int>());

    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int l = 0;
    int r = n+1;
    int k = INT_MAX;
    while (l < r) {
        int x = (l+r)/2;
        int d = sp(1, x, 0);
        if (d == 0) {
            k = min(k, x);
            r = x;
        } else {
            l = x+1;
        }
    }

    cout << k << "\n";

    // for (int i = 1; i <= n; ++i) {
    //     cout << "dp[" << i << "] = " << dp[i] << "\n";
    // }

    // mktree(1);
    // for (int i = 1; i <= n; ++i) {
    //     if (tree[i].size() == 0) cf(i);
    // }
    // int l = 0;
    // int r = n + 1;
    // int res = INT_MAX;
    // while (l < r) {
    //     int k = (l + r) / 2;
    //     int s = sp(1, k, 0);
    //     cout << k << ": "<< s << "\n";
    //     if (s == 0) {
    //         l++;
    //     } else if (s > res) {
    //         r = k - 1;
    //     } else {
    //         res = s;
    //     }
    // }

    return 0;
}
