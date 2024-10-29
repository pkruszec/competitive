#include <iostream>
#include <vector>
#include <stdint.h>
#include <limits.h>

using namespace std;

using s64 = int64_t;

int n = 0;
vector<int> ba;
vector<int> bi;
vector<bool> owner;

bool jealous(bool who)
{
    vector<int> &source = who ? bi : ba;
    s64 sum_this = 0;
    s64 sum_other = 0;
    s64 min_other = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (owner[i] == who) {
            sum_this += source[i];
        } else {
            sum_other += source[i];
            if (source[i] < min_other) min_other = source[i];
        }
        // cout << who << ", " << i << ": " << sum_this << " vs " << sum_other << "\n";
    }

    return sum_this < (sum_other - min_other);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    ba.resize(n);
    bi.resize(n);
    owner.resize(n, false);

    for (auto &x: ba) {
        cin >> x;
    }
    for (auto &x: bi) {
        cin >> x;
    }

    while (jealous(1)) {
        int min = INT_MAX;
        int min_index = -1;
        for (int i = 0; i < n; ++i) {
            if (!owner[i] && ba[i] < min) {
                min = ba[i];
                min_index = i;
            }
        }

        if (min_index < 0) {
            cout << "BUG min_index < 0\n";
            return 0;
        }

        // cout << min_index << "\n";

        owner[min_index] = true;

        // for (auto x: owner) {
        //     cout << x << " ";
        // }
        // cout << "\n";
    }
    
    if (jealous(0)) {
        cout << "BUG jealous\n";
        return 0;
    }

    for (auto x: owner) {
        cout << x << " ";
    }
    cout << "\n";

    return 0;
}
