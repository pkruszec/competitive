#include <iostream>
#include <vector>
#include <stdint.h>
#include <limits.h>
#include <algorithm>

#define NOT_SET (-1)
#define BA 0
#define BI 1

using namespace std;

using s64 = int64_t;

int n = 0;
s64 full_sum_a = 0;
s64 full_sum_i = 0;
s64 sum_a = 0;
s64 sum_i = 0;
s64 min_a = INT_MAX;
vector<int> xs_a;
vector<int> xs_i;
vector<int> ba;
vector<int> bi;
vector<char> owner;

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

    xs_a.resize(n);
    xs_i.resize(n);
    ba.resize(n);
    bi.resize(n);
    owner.resize(n, NOT_SET);

    for (int i = 0; i < n; ++i) {
        xs_a[i] = i;
        xs_i[i] = i;
    }

    for (auto &x: ba) {
        cin >> x;
    }
    for (auto &x: bi) {
        cin >> x;
    }

    sort(xs_a.begin(), xs_a.end(), [](auto a, auto b){
            return ba[a] > ba[b];
        });

    sort(xs_i.begin(), xs_i.end(), [](auto a, auto b){
            return bi[a] > bi[b];
        });

    int pa = 0;
    int pi = 0;
    bool i = false;
    int set = 0;

    while (true) {

        /*
        cout << i << " " << pa << " " << pi << "\n";
        for (auto &x: xs_a) {
            if (owner[x] == NOT_SET) cout << "[";
            cout << ba[x];
            if (owner[x] == NOT_SET) cout << "]";
            cout << " ";
        } cout << "\n";
        for (auto &x: xs_i) {
            if (owner[x] == NOT_SET) cout << "[";
            cout << bi[x];
            if (owner[x] == NOT_SET) cout << "]";
            cout << " ";
        } cout << "\n";
        */

        int idx = -1;
        int bst = -1;
        vector<int> &xs = i ? xs_i : xs_a;
        int fst = i ? pi : pa;
        for (int j = fst; j < xs.size(); ++j) {
            int x = xs[j];
            if (owner[x] == NOT_SET) {
                idx = x;
                bst = j;
                break;
            }
        }

#if 1
        if (idx < 0) {
            cout << "BUG idx < 0\n";
            // return 0;
        }
#endif

        owner[idx] = i;
        set++;

        if (i) {
            pi = bst;
        } else {
            pa = bst;
        }

        i = !i;
        if (set >= n) break;
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
        cout << (int)x << " ";
    }
    cout << "\n";

    return 0;
}
