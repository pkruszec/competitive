#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdint>

using namespace std;

using s64 = long long;

s64 n;
vector<vector<s64>> bd;
vector<vector<pair<s64, s64>>> dp;
vector<vector<bool>> pv;

/*
s64 tz(s64 x)
{
    auto s = to_string(x);
    s64 cnt = 0;
    for (s64 i = s.size()-1; i >= 0; --i) {
        if (s[i] != '0') break;
        cnt++;
    }
    return cnt;
}
*/

s64 tz(s64 x, s64 &mm)
{
    s64 cnt = 0;
    s64 m = 10;
    while (true) {
        if (x % m != 0) break;
        cnt++;
        m *= 10;
    }

    mm = m / 10;
    return cnt;
}

// bool better(s64 a, s64 b)
// {
//     return tz(a) <= tz(b);
// }

void f(s64 i, s64 j)
{
    if (i > n || j > n) return;

    s64 nz = dp[i][j].first;
    s64 base = dp[i][j].second;

    s64 dv = bd[i+1][j];
    s64 rv = bd[i][j+1];

    s64 dt = base * dv;
    s64 dm = 0;
    s64 dz = nz + tz(dt, dm);
    s64 dr = (dt / dm) % 1000;

    s64 rt = base * rv;
    s64 rm = 0;
    s64 rz = nz + tz(rt, rm);
    s64 rr = (rt / rm) % 1000;

    if (dz <= dp[i+1][j].first) {
        // cout << dz << " < " << dp[i+1][j].first << "\n";

        dp[i+1][j] = {dz, dr};
        pv[i+1][j] = true;
    }

    if (rz <= dp[i][j+1].first) {
        dp[i][j+1] = {rz, rr};
        pv[i][j+1] = false;
    }

    f(i + 1, j);
    f(i, j + 1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);


    // s64 mm = -1;
    // cout << tz(13000000, mm) << " " << mm << "\n";
    // return 0;

#if 1
    cin >> n;
    bd.resize(n+2, vector<s64>(n+2, 1));
    dp.resize(n+2, vector<pair<s64, s64>>(n+2, {0, 1}));
    pv.resize(n+2, vector<bool>(n+2, false));

    for (s64 i = 1; i <= n; ++i) {
        for (s64 j = 1; j <= n; ++j) {
            cin >> bd[i][j];
        }
    }

    // dp[1][1] = bd[1][1];

    s64 mm = 0;
    s64 nz = tz(bd[1][1], mm);

    dp[1][1] = {nz, bd[1][1] / mm};

    f(1, 1);

    /*
    for (s64 i = 1; i <= n; ++i) {
        for (s64 j = 1; j <= n; ++j) {

            s64 base = bd[i][j];

            pair<s64, s64> up =   dp[i - 1][j];
            pair<s64, s64> left = dp[i][j - 1];

            if (up.first > left.first) {
                s64 r = base * up.second;
                s64 m = 0;
                s64 cnt = up.first + tz(r, m);
                s64 res = (r / m) % 1000;
                dp[i][j] = {cnt, res};

                pv[i][j] = true;
            } else if (up.first < left.first) {
                s64 r = base * left.second;
                s64 m = 0;
                s64 cnt = left.first + tz(r, m);
                s64 res = (r / m) % 1000;
                dp[i][j] = {cnt, res};

                pv[i][j] = false;
            } else {
                if (up.second > left.second) {
                    s64 r = base * up.second;
                    s64 m = 0;
                    s64 cnt = up.first + tz(r, m);
                    s64 res = (r / m) % 1000;
                    dp[i][j] = {cnt, res};

                    pv[i][j] = true;
                } else {
                    s64 r = base * left.second;
                    s64 m = 0;
                    s64 cnt = left.first + tz(r, m);
                    s64 res = (r / m) % 1000;
                    dp[i][j] = {cnt, res};

                    pv[i][j] = false;
                }
            }

            // s64 dt = base * dv;
            // s64 dm = 0;
            // s64 dz = nz + tz(dt, dm);
            // s64 dr = (dt / dm) % 1000;

            // s64 rt = base * rv;
            // s64 rm = 0;
            // s64 rz = nz + tz(rt, rm);
            // s64 rr = (rt / rm) % 1000;



            // dp[i][j] = {cnt, res};

            // if (up < left)
            //     pv[i][j] = true;
        }
    }
        */

    #if 1
    for (s64 i = 1; i <= n; ++i) {
        for (s64 j = 1; j <= n; ++j) {
            cerr << dp[i][j].second << "e" << dp[i][j].first << " ";
        }
        cerr << "\n";
    }

    for (s64 i = 1; i <= n; ++i) {
        for (s64 j = 1; j <= n; ++j) {
            if (i == 1 && j == 1) {
                cerr << ". ";
            } else if (pv[i][j]) {
                cerr << "^ ";
            } else if (!pv[i][j]) {
                cerr << "< ";
            } else {
                cerr << "! ";
            }
        }
        cerr << "\n";
    }
    #endif

    vector<bool> path;
    s64 i = n;
    s64 j = n;
    while (true) {
        if (i == 1 && j == 1) break;
        bool x = pv[i][j];
        if (x) {
            i--;
        } else {
            j--;
        }
        path.push_back(x);
    }

    cout << dp[n][n].first << "\n";
    for (s64 i = path.size() - 1; i >= 0; --i) {
        cout << (path[i]?'D':'R');
    }
    cout << "\n";
#endif

    return 0;
}
///
