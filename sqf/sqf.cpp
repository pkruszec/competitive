#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

/*
    if (k == n && b_count > 0) {
        cout << "-1\n";
        return 0;
    }
*/

    while (1) {
        // if (all_of(s.begin(), s.end(), [](auto c){return c == true;})) break;

        if (b_count == 0) break;

        int best_i = -1;
        int best_c = 0;
        for (int i = 0; i <= n-k; ++i) {
            // if (s[i] != 0) continue;
            int c = left_b_count(i);
            if (c > best_c) {
                best_c = c;
                best_i = i;
            }
        }

        if (best_i < 0) {
            cout << "-1\n";
            return 0;
        }

        // for (auto c: s) {
        //     cout << c;
        // }
        // cout << " ";
        // cout << " " << best_i << " (" << best_c << ")\n";

        flip(best_i);
        moves++;

        // if (moves % 2500 == 0) cout << moves << "\n";
        // cout << moves << "\n";
    }

    // for (auto c: s) {
    //     cout << c;
    // }
    // cout << "\n";
    // cout << "       ";

    cout << moves << "\n";

    return 0;
}
