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
    int n, m;
    cin >> n >> m;

    vector<int> k(n+1);
    vector<int> d(n+1);
    vector<int> w(m+1);

    for (int i = 1; i <= n; ++i) {
        cin >> k[i];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> w[i];
    }

    d[1] = k[1];
    for (int i = 2; i <= n; ++i) {
        d[i] = min(d[i - 1], k[i]);
    }

    int last = n+1;
    for (int j = 1; j <= m; ++j) {
        int a = 0;
        int b = last - 1;
        while (a < b) {
            int c = (a+b)/2 + 1;
            if (d[c] < w[j]) {
                b = c - 1;
            } else {
                a = c;
            }
        }
        last = a;
        if (last < 1) {
            cout << "0\n";
            return 0;
        }
    }

    cout << last << "\n";

    return 0;
}