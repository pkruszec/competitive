#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdint.h>

#define SGN(x) ((0<(x)) - ((x)<0))

#ifndef MEASURE
# define MEASURE 0
#endif

using namespace std;

int moves = 0;
int b_count = 0;
int n, k;
vector<bool> s;
vector<int> counts;

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
        if (s[j]) return c;
        c++;
    }
    return c;
}

// >0 black
// <0 white
static int left_count(int i)
{
    int mx = i+k;
    int c = 0;
    int d = s[i];

    for (int j = i; j < mx; ++j) {
        if (s[j] != d) break;
        c++;
    }
    return d == 1 ? -c : c;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    s.resize(n, false);
    counts.resize(n-k+1, 0);

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

    for (int i = 0; i <= n-k; ++i) {
        counts[i] = left_count(i);
    }

#if MEASURE
    uint64_t get_time = 0;
    uint64_t flip_time = 0;
    int cmoves = 0;
#endif

    while (1) {
        // cout << "{";
        // for (auto c: counts) {
        //     cout << c << " ";
        // }
        // cout << "}\n";

        if (b_count == 0) break;

#if MEASURE
        uint64_t t0, t1;
        t0 = __rdtsc();
#endif

        // int cnt = 0;

        int best_i = -1;
        int best_c = 0;
        for (int i = 0; i <= n-k; ++i) {
            if (counts[i] > best_c) {
                best_c = counts[i];
                best_i = i;
            }
            // cnt++;
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

        /*
        0123456
        */

        flip(best_i);

#if MEASURE
        t0 = __rdtsc();
#endif

        // counts[best_i] = -counts[best_i];
        
        int min_i = best_i;
        int max_i = min(best_i+k, n-k);

        for (int i = min_i; i <= max_i; ++i) {
            
            #if 0
            int prev = counts[i-1];
            int absprev = abs(prev);
            int sgnprev = SGN(prev);
            int curr = counts[i];
            int idx = i-best_i;

            if (idx < absprev) {
                // TODO: we should still count the left ones, but from the point where we can't 
                // deduce it from the counts.
                // affected by change 
                int res = absprev - idx;
                if (SGN(curr) == sgnprev && curr > res) {
                    res = abs(curr);
                }
                counts[i] = res * sgnprev;
            }
            #endif

            //int pc = counts[i];
            counts[i] = left_b_count(i);
        }

#if MEASURE
        t1 = __rdtsc();
        flip_time += t1-t0;
#endif

        moves++;

        // if (moves % 1000 == 0) cout << best_c << "\n";

#if MEASURE
        cmoves++;
        if (cmoves >= 1000) {
            cout << max_i-min_i << " " << moves << " get: " << get_time/cmoves << "/move flip: " << flip_time/(cmoves) << "/move \n";
            flip_time = 0;
            get_time = 0;
            cmoves = 0;
        }
#endif

    }

    cout << moves << "\n";

    return 0;
}
