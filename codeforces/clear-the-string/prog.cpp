#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits.h>

using namespace std;

typedef pair<char, int> P;

int best = INT_MAX;

void del_update(vector<P> &p, int index)
{
    p.erase(p.begin() + index);

    for (auto it = p.begin(); it != p.end();) {
        if (it + 1 != p.end() && (it + 1)->first == it->first) {
            (it + 1)->second += it->second;
            it = p.erase(it);
        } else {
            ++it;
        }
    }
}

void find(vector<P> p, int moves)
{
    if (p.size() == 0) {
        best = min(best, moves);
    }

    for (int i = 0; i < p.size(); ++i) {
        auto r = p;
        del_update(r, i);
        find(r, moves + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    string s;
    cin >> n >> s;
    vector<P> p;

    int cp = -1;
    for (int i = 0; i < s.size(); ++i) {
        if (cp < 0) {
            p.push_back({s[i], 1});
            cp = p.size() - 1;
        } else {
            if (s[i] == p[cp].first) {
                p[cp].second++;
            } else {
                p.push_back({s[i], 1});
                cp = p.size() - 1;
            }
        }
    }

    find(p, 0);
    cout << best << "\n";

    // for (auto &[c, d]: p) {
    //     cout << c << ":" << d << " ";
    // }
    // cout << "\n";

    return 0;
}

/*
 abababa
 4
*/