#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <stdint.h>

using namespace std;

typedef long long s64;

#define REP(i, n) for (s64 i = 0; i < (n); ++i)
#define IT(xs)    for (auto &it: (xs))

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    s64 n, m;
    cin >> n >> m;

    vector<s64> c(n);
    vector<s64> s(n);
    vector<vector<s64>> mc(m, vector<s64>(n));

    REP(i, n) cin >> c[i];
    REP(i, n) cin >> s[i];

    REP(i, m) {
        REP(j, n) {
            cin >> mc[i][j];
        }
    }

    vector<s64> state = s;
    //# cerr << "STATE: "; IT(state) { cerr << it << " "; } cerr << "\n";

    REP(i, m) {
        //# cerr << "######################## MONTH " << i << " ########################" << "\n";

        vector<s64> &cand = mc[i];
        vector<s64> nstate(n, -1);

        vector<s64> sor(n);
        REP(cit, n) sor[cit] = cit;
        sort(sor.begin(), sor.end(), [&](auto a, auto b) {
            return cand[a] > cand[b];
        });

        REP(cit, n) {
            s64 v = cand[sor[cit]];
            //# cerr << "=========== CAND "<< v << " ===========\n";
    
            s64 best = -1;
            s64 min_cost = LLONG_MAX;

            REP(j, n) {
                s64 p = state[j];
                s64 r = c[j];
    
                s64 cost = (v - p) * r;
    
                if (cost >= 0 && nstate[j] < 0 && cost < min_cost) {
                    min_cost = cost;
                    best = j;
                    //# cerr << p << ": (" << v << " - " << p << ") * " << r << " = " << cost << "\n";
                }
            }

            if (best < 0) {
                cout << "NIE\n";
                return 0;
            }

            //# cerr << best << " (" << v << ") --> " << min_cost << "\n";

            nstate[best] = v;
        }

        state = nstate;
        //# cerr << "STATE: "; IT(state) { cerr << it << " "; } cerr << "\n";
    }

    s64 total = 0;
    REP(i, n) {
        total += (state[i] - s[i]) * c[i];
    }

    cout << total << "\n";

    return 0;
}

// 3 2 4 7
// 3 5 7 10