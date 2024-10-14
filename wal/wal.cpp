//
// Walki robotów (wal)
// Paweł Kruszec
//

#include <iostream>
#include <vector>
#include <stdint.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    // s are unique
    // z are unique
    // take advantage of this fact?

    // linked list?
    vector<pair<int, int>> xs(n);

    for (int i = 0; i < n; ++i) {
        cin >> xs[i].first >> xs[i].second;
    }

    while (!xs.empty()) {
        if (xs.size() == 1) {
            cout << "NIE\n";
            return 0;
        }

        auto [s0, z0] = xs[0];
        auto [s1, z1] = xs[1];

        bool remove0 = (s0 < s1) || (z0 < z1);
        bool remove1 = (s1 < s0) || (z1 < z0);
        if (remove0) {
            xs.erase(xs.begin());
            if (remove1) {
                xs.erase(xs.begin());
            }
        } else if (remove1) {
            xs.erase(xs.begin() + 1);
        }
    }

    cout << "TAK\n";

/*
    for (auto [s, z]: xs) {
        cout << s << " " << z << "\n";
    }
*/

    return 0;
}
