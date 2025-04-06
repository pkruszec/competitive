#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        if (k % 2 == 0) {
            cout << "-1\n";
            continue;
        } else {
            cout << k << " ";
            for (int i = 1; i <= k-1; ++i) {
                cout << i << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}
