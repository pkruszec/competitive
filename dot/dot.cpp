#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdint.h>
#include <limits.h>

#define SGN(x) ((0<(x)) - ((x)<0))

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n0, n1;
    cin >> n0 >> n1;
    vector<int> v0(n0, 0);
    vector<int> v1(n1, 0);

    for (int i = 0; i < n0; ++i) {
        cin >> v0[i];
    }

    for (int i = 0; i < n1; ++i) {
        cin >> v1[i];
    }

    int sm = 0;

    vector<pair<int, int>> possible {};

    // MEASURE
    // uint64_t t0, t1;
    // t0 = __rdtsc();

    for (int i = 0; i < n0; ++i) {
        int current = v0[i];
        int sgn = SGN(current);
        if (current == 0) continue;

        for (int j = 0; j < n1; ++j) {
            if (SGN(v1[j]) == sgn) {
                possible.push_back(pair<int, int>(i, j));
            }
        }
    }

    // MEASURE
    // t1 = __rdtsc();
    // cout << t1-t0 << "\n";

    int p0 = 0;
    int p1 = 0;

    int64_t sm0 = 0;

    // MEASURE
    // t0 = __rdtsc();

    while ((p0 < n0)) {

        int64_t best_p1_product = INT64_MIN;
        int64_t best_p1_value = INT64_MIN;
        int64_t best_p1 = -1;
        for (int i = 0; i < possible.size(); ++i) {
            auto &p = possible[i];

            if (!(p.first == p0 && p.second >= p1)) continue;

            int product = v0[p.first]*v1[p.second];
            int64_t value = product;

            for (int j = 0; j < possible.size(); ++j) {
                if (i == j) continue;
                auto &r = possible[j];
                if (!(r.first > p.first && r.second < p.second)) continue;
                value -= v0[r.first]*v1[r.second];

                if (value <= best_p1_value) {
                    break;
                }
            }

            if (value > best_p1_value) {
                best_p1 = p.second;
                best_p1_product = product;
                best_p1_value = value;
            }
        }

        p0++;
        if (best_p1 >= 0) {
            sm0 += best_p1_product;
            p1 = best_p1+1;
        }

    }

    // MEASURE
    // t1 = __rdtsc();
    // cout << t1-t0 << "\n";

    p0 = 0;
    p1 = 0;
    int64_t sm1 = 0;

    // MEASURE
    // t0 = __rdtsc();

    while ((p1 < n1)) {

        int64_t best_p0_product = INT64_MIN;
        int64_t best_p0_value = INT64_MIN;
        int64_t best_p0 = -1;
        for (int i = 0; i < possible.size(); ++i) {
            auto &p = possible[i];

            if (!(p.second == p1 && p.first >= p0)) continue;

            int product = v0[p.first]*v1[p.second];
            int64_t value = product;

            for (int j = 0; j < possible.size(); ++j) {
                if (i == j) continue;
                auto &r = possible[j];
                if (!(r.second > p.second && r.first < p.first)) continue;
                value -= v0[r.first]*v1[r.second];

                if (value <= best_p0_value) {
                    break;
                }
            }

            if (value > best_p0_value) {
                best_p0 = p.first;
                best_p0_product = product;
                best_p0_value = value;
            }
        }

        p1++;
        if (best_p0 >= 0) {
            sm1 += best_p0_product;
            p0 = best_p0+1;
        }

    }

    // MEASURE
    // t1 = __rdtsc();
    // cout << t1-t0 << "\n";

    sm = max(sm0, sm1);

    if (sm == 0) {
        int min0 = INT_MAX;
        int min1 = INT_MAX;
        for (int i = 0; i < n0; ++i) {
            if (abs(v0[i]) < abs(min0)) min0 = v0[i];
        }
        for (int i = 0; i < n1; ++i) {
            if (abs(v1[i]) < abs(min1)) min1 = v1[i];
        }

        sm += min0*min1;
    }

    cout << sm << "\n";

    return 0;
}
