#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    vector<vector<int>> V(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        int c = n-i;
        for (int j = 0; j < c; ++j) {
            int x;
            cin >> x;
            // cout << i << "," << i+j << " -> " << x << "\n";
            V[i][i+j] = x;
        }
    }

    return 0;
}
