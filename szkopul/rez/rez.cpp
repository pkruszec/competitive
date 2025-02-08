#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>
#include <queue>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    vector<pair<int, int>> in(n+1);
    vector<int> tm(n+1);

    for (int i = 1; i <= n; ++i) {
        cin >> in[i].first >> in[i].second;
    }

    sort(in.begin(), in.end(), [](auto a, auto b) {
        return a.second <= b.second;
    });

    for (int i = 1; i <= n; ++i) {
        auto [p, k] = in[i];

        int t1 = tm[i - 1];
        int t2 = 0;

        int mx = 0;

        int l = 0;
        int r = i;
        while (l < r) {
            int j = (l+r)/2;
            int e = in[j].second;

            if (e <= p && j > mx) mx = j;

            if (e <= p) {
                l = j+1;
            } else if (e > p) {
                r = j;
            }
        }

        // for (int j = i-1; j > 0; --j) {
        //     if (in[j].second <= p) {
        //         mx = j;
        //         break;
        //     }
        // }

        // for (int j = 1; j <= i; ++j) {
        //     if (in[j].second > p) {
        //         mx = j-1;
        //         break;
        //     }
        // }

        t2 = tm[mx] + k - p;
        tm[i] = max(t1, t2);
    }

    int result = tm[n];
    cout << result << "\n";

    return 0;
}
