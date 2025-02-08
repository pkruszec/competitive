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

    vector<pair<int, int>> in(n);

    for (int i = 0; i < n; ++i) {
        cin >> in[i].first >> in[i].second;
    }

    sort(in.begin(), in.end(), [](auto a, auto b) {
        return (a.second - a.first) > (b.second - b.first);
    });

    vector<int> s;
    for (int i = 0; i < n; ++i) {
        auto [l, r] = in[i];

        bool ok = true;
        for (auto j: s) {
            auto [l1, r1] = in[j];

            if (l < r1 && l1 <= r) {
                ok = false;
                break;
            }
        }

        if (ok) {
            s.push_back(i);
        }
    }

    int sum = 0;
    for (auto i: s) {
        auto [l, r] = in[i];
        sum += r-l;
    }

    cout << sum << "\n";

    // cout << accumulate(s.begin(), s.end(), 0) << "\n";

    return 0;
}

/*
   -----
  ------
----
      ---
012345678
*/