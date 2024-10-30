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
    s64 max_other = 0;
    for (int i = 0; i < n; ++i) {
        if (owner[i] == who) {
            sum_this += source[i];
        } else {
            sum_other += source[i];
            if (source[i] > max_other) max_other = source[i];
        }
    }

    // cout << who << ": " << sum_this << " vs " << sum_other << "\n";
    return sum_this < (sum_other - max_other);
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

    owner.resize(n, false);
    sum_a = full_sum_i;
    sort(xs.begin(), xs.end(), [](auto a, auto b){
            return bi[a] > bi[b];
        });

    int p = 0;
    while (true) {
        int min = INT_MAX;
        int best_index = -1;

        for (int i = p; i < xs.size(); ++i) {
            int x = xs[i];
            if (!owner[x]) {
                best_index = x;
                break;
            }
        }

        for (int i = xs.size() - 1; i >= p; --i) {
            int x = xs[i];
            if (!owner[x]) {
                min = bi[x];
                break;
            }
        }

        if (best_index < 0) {
            cout << "BUG best_index < 0\n";
            return 0;
        }

        min_a = min;
        if (sum_i >= (sum_a-min_a)) break;

        sum_a -= bi[best_index];
        sum_i += bi[best_index];
        owner[best_index] = true;
        p = best_index;
    }

#if 0
    if (full_sum_a > full_sum_i) {
        owner.resize(n, false);
        sum_a = full_sum_i;
        sort(xs.begin(), xs.end(), [](auto a, auto b){
                return bi[a] > bi[b];
            });

        int p = 0;
        while (true) {
            int min = INT_MAX;
            int best_index = -1;

            for (int i = p; i < xs.size(); ++i) {
                int x = xs[i];
                if (!owner[x]) {
                    best_index = x;
                    break;
                }
            }

            for (int i = xs.size() - 1; i >= p; --i) {
                int x = xs[i];
                if (!owner[x]) {
                    min = bi[x];
                    break;
                }
            }

            if (best_index < 0) {
                cout << "BUG best_index < 0\n";
                return 0;
            }

            min_a = min;
            if (sum_i >= (sum_a-min_a)) break;

            sum_a -= bi[best_index];
            sum_i += bi[best_index];
            owner[best_index] = true;
            p = best_index;
        }
    }
    
    else {
        owner.resize(n, true);
        sum_a = full_sum_a;
        sort(xs.begin(), xs.end(), [](auto a, auto b){
                return ba[a] > ba[b];
            });

        int p = 0;
        while (true) {
            int min = INT_MAX;
            int best_index = -1;

            for (int i = p; i < xs.size(); ++i) {
                int x = xs[i];
                if (owner[x]) {
                    best_index = x;
                    break;
                }
            }

            for (int i = xs.size() - 1; i >= p; --i) {
                int x = xs[i];
                if (owner[x]) {
                    min = ba[x];
                    break;
                }
            }

            if (best_index < 0) {
                cout << "BUG best_index < 0\n";
                return 0;
            }

            min_a = min;
            if (sum_i >= (sum_a-min_a)) break;

            sum_a -= ba[best_index];
            sum_i += ba[best_index];
            owner[best_index] = false;
            p = best_index;
        }
    }
#endif

    if (jealous(0)) {
        for (int i = 0; i < n; ++i) {
            owner[i] = !owner[i];
        }
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
