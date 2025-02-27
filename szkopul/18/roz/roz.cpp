#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <limits.h>

#define N 1000000

using namespace std;

template<typename T>
void print1(T x)
{
    cout << x << " ";
}
template<typename... Ts>
void print(Ts &&...args)
{
    (print1(args), ...);
    cout << "\n";
}

int pre[N][26] = {};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;

    for (int i = 1; i <= n; ++i) {
        for (char k = 0; k < 26; ++k) {
            pre[i][k] = pre[i - 1][k];
        }
        pre[i][s[i-1] - 'a']++;
    }

    // for (int i = 1; i <= n; ++i) {
    //     print("pre[", i, "]:");
    //     for (char k = 'a'; k <= 'z'; ++k) {
    //         int x = pre[i][k];
    //         if (x < 1) continue;
    //         print("   ", k, "=", x);
    //     }
    // }

    vector<int> cnt(128);

    int res = 0;
    for (int i = 1; i < n; ++i) {
        
        // print("i:", i);

        for (int j = i+1; j <= n; ++j) {
            int ma = 0;
            int mi = INT_MAX;

            // print("  j:", j);

            for (char k = 0; k < 26; ++k) {
                cnt[k] = pre[j][k] - pre[i-1][k];

                // if (cnt[k] != 0)print("    cnt", k, "=", cnt[k]);
            }

            for (char k = 0; k < 26; ++k) {
                ma = max(ma, cnt[k]);
                if (cnt[k] >= 1) {
                    mi = min(mi, cnt[k]);

                    // print("    mi:", k, cnt[k]);
                }
            }

            res = max(res, ma-mi);
        }

    }

    // print("============== RESULT:");
    cout << res << "\n";
    return 0;
}