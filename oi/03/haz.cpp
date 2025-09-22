#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    vector<unordered_map<int, int>> cnt(n + 1);
    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int x;
            cin >> x;
            cnt[i][x] ++;
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << i << " :: { ";
        for (auto &[k, v] : cnt[i]) {
            cout << v << " x " << k << "  ";
        }
    }

    return 0;
}
