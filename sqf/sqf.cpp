#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdint.h>

#ifndef MEASURE
# define MEASURE 0
#endif

using namespace std;

int moves = 0;
int b_count = 0;
int n, k;
vector<bool> s;

static void flip(int i)
{
    int mx = i+k;
    for (int j = i; j < mx; ++j) {
        s[j] = !s[j];
        b_count += s[j] ? -1 : 1;
    }
}

static int left_b_count(int i)
{
    int mx = i+k;
    int c = 0;
    for (int j = i; j < mx; ++j) {
        bool x = s[j];
        if (x) break;
        c++;
    }
    return c;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> k;
    s.resize(n, false);

    for (int i = 0; i < n; ++i) {
        char x;
        cin >> x;
        s[i] = x == 'w';
        if (!s[i]) b_count++;
    }

    if (k == 1) {
        cout << b_count << "\n";
        return 0;
    }

#if MEASURE
    uint64_t get_time = 0;
    uint64_t flip_time = 0;
    int cmoves = 0;
#endif

    while (1) {
        if (b_count == 0) break;

#if MEASURE
        uint64_t t0, t1;
        t0 = __rdtsc();
#endif

        int best_i = -1;
        int best_c = 0;
        for (int i = 0; i <= n-k; ++i) {
            int c = left_b_count(i);
            if (c > best_c) {
                best_c = c;
                best_i = i;
            }
        }

#if MEASURE
        t1 = __rdtsc();
        get_time += t1-t0;
#endif

        if (best_i < 0) {
            cout << "-1\n";
            return 0;
        }

        // for (auto c: s) {
        //     cout << c;
        // }
        // cout << " ";
        // cout << " " << best_i << " (" << best_c << ")\n";

#if MEASURE
        t0 = __rdtsc();
#endif

        flip(best_i);
        moves++;

#if MEASURE
        t1 = __rdtsc();
        flip_time += t1-t0;
        cmoves++;
        if (cmoves >= 1000) {
            cout << moves << " get: " << get_time/cmoves << "/move flip: " << (double)flip_time/(double)(cmoves) << "/move \n";
            flip_time = 0;
            get_time = 0;
            cmoves = 0;
        }
#endif

    }

    cout << moves << "\n";

    return 0;
}
