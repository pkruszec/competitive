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
vector<vector<s64>> dp;
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

s64 tz(s64 x)
{
    s64 cnt = 0;
    s64 m = 10;
    while (true) {
        if (x % m != 0) break;
        cnt++;
        m *= 10;
    } 
    return cnt;
}

bool better(s64 a, s64 b)
{
    return tz(a) <= tz(b);
}

void f(s64 i, s64 j)
{
    if (i > n || j > n) return;

    s64 down  = dp[i][j] * bd[i+1][j];
    s64 right = dp[i][j] * bd[i][j+1];

    if (better(down, dp[i+1][j])) {
        dp[i+1][j] = down;
        pv[i+1][j] = true;
    }

    if (better(right, dp[i][j+1])) {
        dp[i][j+1] = right;
        pv[i][j+1] = false;
    }

    f(i + 1, j);
    f(i, j + 1);
}

int main()
{

    // cout << tz() << "\n";
    // return 0;

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    bd.resize(n+2, vector<s64>(n+2, 1000000000));
    dp.resize(n+2, vector<s64>(n+2, 1000000000));
    pv.resize(n+2, vector<bool>(n+2, false));

    for (s64 i = 1; i <= n; ++i) {
        for (s64 j = 1; j <= n; ++j) {
            cin >> bd[i][j];
        }
    }

    dp[1][1] = bd[1][1];

    f(1, 1);

    // for (s64 i = 1; i <= n; ++i) {
    //     for (s64 j = 1; j <= n; ++j) {
    //         s64 up =   dp[i - 1][j];
    //         s64 left = dp[i][j - 1];
    //         dp[i][j] = bd[i][j] + min(up, left);
    //         if (up < left)
    //             pv[i][j] = true;
    //     }
    // }

    #if 1
    for (s64 i = 1; i <= n; ++i) {
        for (s64 j = 1; j <= n; ++j) {
            cerr << dp[i][j] << " ";
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

    cout << tz(dp[n][n]) << "\n";
    for (s64 i = path.size() - 1; i >= 0; --i) {
        cout << (path[i]?'D':'R');
    }
    cout << "\n";

    return 0;
}
///
