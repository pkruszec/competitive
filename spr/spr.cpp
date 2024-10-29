#include <iostream>
#include <vector>
#include <stdint.h>
#include <limits.h>
#include <algorithm>

using namespace std;

using s64 = int64_t;

int n = 0;
s64 full_sum_a = 0;
s64 full_sum_i = 0;
s64 sum_a = 0;
s64 sum_i = 0;
s64 min_a = INT_MAX;
vector<int> xs;
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
    }

    // cout << who << ": " << sum_this << " vs " << sum_other << "\n";
    return sum_this < (sum_other - min_other);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    if (n == 1) {
        cout << "0\n";
        return 0;
    }
    if (n == 2) {
        cout << "0 1\n";
        return 0;
    }

    xs.resize(n);
    ba.resize(n);
    bi.resize(n);
    owner.resize(n, false);

    for (int i = 0; i < n; ++i) {
        xs[i] = i;
    }

    for (auto &x: ba) {
        cin >> x;
        full_sum_a += x;
    }
    for (auto &x: bi) {
        cin >> x;
        full_sum_i += x;
    }

    sum_a = full_sum_i;

    sort(xs.begin(), xs.end(), [](auto a, auto b){
            return bi[a] > bi[b];
            // return bi[a] > bi[b] + ba[a] < ba[b];
        });

    // for (auto x: xs) {
    //     cout << x << " ";
    // }cout << "\n";

    // cout << sum_i << " vs " << sum_a << "-" << min_a << "=" << (sum_a-min_a) << "\n";

    int p = 0;
    while (true) {
        int min = INT_MAX;
        int best_index = -1;

        for (int i = p; i < xs.size(); ++i) {
            int x = xs[i];
            if (!owner[x]) {
                best_index = x;
                // min = bi[x];
                break;
            }
        }

        for (int i = xs.size() - 1; i >= p; --i) {
            int x = xs[i];
            if (!owner[x]) {
                min = bi[x];
                // min = bi[x];
                break;
            }
        }

        if (best_index < 0) {
            cout << "BUG min_index < 0\n";
            return 0;
        }

        min_a = min;
        // cout << min << ": " << sum_i << " vs " << sum_a << "-" << min_a << "=" << (sum_a-min_a) << "\n";
        if (sum_i >= (sum_a-min_a)) break;

        // cout << min_index << "\n";

        sum_a -= bi[best_index];
        sum_i += bi[best_index];
        owner[best_index] = true;
        p = best_index;

        // for (auto x: owner) {
        //     cout << x << " ";
        // }
        // cout << "\n";
    }
    
#if 1
    if (jealous(0)) {
        cout << "BUG baj jealous\n";
        // return 0;
    }
    if (jealous(1)) {
        cout << "BUG bit jealous\n";
        // return 0;
    }
#endif

    for (auto x: owner) {
        cout << x << " ";
    }
    cout << "\n";

    return 0;
}
