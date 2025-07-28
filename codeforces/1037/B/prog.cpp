#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        int c = 0;
        int s = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i] == 0 || s == k) {
                s++;
            } else {
                s = 0;
            }

            if (s > k) {
                c++;
                s = 0;
            }
        }

        if(s >= k) {
            c++;
        }

        cout << c << "\n";
    }
    return 0;
}

// ddd
//
//   ddd
// xxxxx
