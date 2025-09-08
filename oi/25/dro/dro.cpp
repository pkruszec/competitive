#include <iostream>
#include <vector>
#include <algorithm>
#define REP(i, n) for (int i = 0; i < n; ++i)

using namespace std;

vector<vector<int>> adj;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    adj.resize(n+1, vector<int>());

    REP(i, m) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }
    


    // REP(i, n) {
    //     cout << i << ": ";
    //     for(auto x: adj[i]) {
    //         cout << x << " ";
    //     }
    //     cout << "\n";
    // }

    return 0;
}
