#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> seg;

pair<bool, vector<pair<int, int>>> check(int i, int l, int r, vector<pair<int, int>> &h)
{
    if (l >= r) return {true, h};
    for (int j = 0; j < i; ++j) {
        auto [xl, xr] = seg[j];
        if (xl == l && xr < r) {
            auto c = h;
            c.push_back(seg[j]);
            auto pr = check(i, xr+1, r, c);
            if (pr.first) {
                return pr;
            }
        }
    }
    return {false, {}};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    string str;
    cin >> n >> str;

    vector<char> s(n);
    for (int i = 0; i < n; ++i) {
        s[i] = str[i] - 'a';
    }

    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            int c[26] = {};

            for (int i = l; i <= r; ++i) {
                c[s[i]]++;
            }

            bool ok = true;
            bool got = false;
            for (int i = 0; i < 26; ++i) {
                if (c[i] % 2 != 0) {
                    if (got) {
                        ok = false;
                        break;
                    }
                    got = true;
                }
            }

            if (ok) {
                seg.push_back({l, r});
                // for (int i = l; i <= r; ++i) {
                //     cout << str[i];
                // }
                // cout << "\n";
            }
        }
    }

    sort(seg.begin(), seg.end(), [](auto x, auto y) {
        return (x.second-x.first + 1) > (y.second-y.first + 1);
    });

    // for (auto [l, r]: seg) {
    //     for (int i = l; i <= r; ++i) {
    //         cout << str[i];
    //     }
    //     cout << "\n";
    // }

    for (int i = 0; i < seg.size(); ++i) {
        auto [l, r] = seg[i];
        // 0<l; r+1<n;

        vector<pair<int, int>> h;

        h = {};
        auto [lok, ls] = check(i, 0, l, h);
        if (!lok) continue;
        h = {};
        auto [rok, rs] = check(i, r+1, n, h);
        if (!rok) continue;

        cout << r-l+1 << "\n";
        cout << ls.size() + 1 + rs.size() << "\n";
        for (auto [xl, xr]: ls) {
            cout << xl+1 << " " << xr+1 << "\n";
        }

        cout << l+1 << " " << r+1 << "\n";

        for (auto [xl, xr]: rs) {
            cout << xl+1 << " " << xr+1 << "\n";
        }
        break;
    }

    //cout << s << "\n";
    return 0;
}

//
// abba
// b:2 a:2
//
// baoab
// bbaao
//
// b:2 a:2 o:3 x: 3
//
// ababeae
// beaaaeb
//