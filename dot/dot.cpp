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
    int n0, n1;
    cin >> n0 >> n1;
    vector<int> v0(n0+1, 0);
    vector<int> v1(n1+1, 0);

    for (int i = 0; i < n0; ++i) {
        cin >> v0[i];
    }

    for (int i = 0; i < n1; ++i) {
        cin >> v1[i];
    }

    int sm = 0;
    int p0 = 0;
    int p1 = 0;

    int mn = min(n0, n1);
    for (int i = 0; i < mn; ++i) {
        int x0 = v0[p0];
        int x1 = v1[p1];

        int sg0 = SGN(x0);
        int sg1 = SGN(x1);

        // cout << p0 << "," << p1 << "\n";

        /*if (sg0 == sg1) {
            sm += x0*x1;
            p0++;
            p1++;
        }
        else */{
            int f0 = -1;
            int f1 = -1;
            int m0 = 0;
            int m1 = 0;

            for (int j = p0; j < n0; ++j) {
                // if (j == p0) continue;
                int x = v0[j];
                int a = abs(x);
                if (SGN(x) == sg1 && a > m0) {
                    m0 = a;
                    f0 = j;
                }
            }

            for (int j = p1; j < n1; ++j) {
                // if (j == p1) continue;
                int x = v1[j];
                int a = abs(x);
                if (SGN(x) == sg0 && a > m1) {
                    m1 = a;
                    f1 = j;
                }
            }

            int mf0 = m0*(f0 >= 0);
            int mf1 = m1*(f1 >= 0);

            int vx0 = mf0*sg1 * x1;
            int vx1 = mf1*sg0 * x0;

            // if (f0 < 0 && f1 < 0) {
            //     sm += x1*x0;
            //     break;
            // }

            if (vx0 == 0 && vx1 == 0) {
                p0++;
                p1++;
                continue;
            }

            int r0 = 3;
            int r1 = 5;
            bool fst = (vx0*r0 - (f0-p0)*r1) >= (vx1*r0 - (f1-p1)*r1);
            if (f0 < 0) fst = false;

            if (fst) {
                sm += vx0;
                p0 = f0+1;
            } else {
                sm += vx1;
                p1 = f1+1;
            }

            // if (m0 > m1) {
            //     p0 = f0;
            //     sm += (v0[p0] * x1);

            //     cout << x1 << ", " << v0[p0] << "\n";
            // } else {
            //     p1 = f1;
            //     sm += (v1[p1] * x0);

            //     cout << x0 << ", " << v1[p1] << "\n";
            // }
        }
    }

    if (sm == 0) {
        int min0 = INT_MAX;
        int min1 = INT_MAX;
        for (int i = 0; i < n0; ++i) {
            if (v0[i] < min0) min0 = v0[i];
        }
        for (int i = 0; i < n1; ++i) {
            if (v1[i] < min1) min1 = v1[i];
        }

        sm += min0*min1;
    }

    cout << sm << "\n";

    // int c = 0;
    // vector<int> d(min(n0, n1));
    // cout << better << "\n";

    return 0;
}
