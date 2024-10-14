//
// Walki robotów (wal)
// Paweł Kruszec
//

#include <iostream>
#include <vector>
#include <stdint.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

/*
    if (n < 2) {
        cout << "NIE\n";
        return 0;
    }
*/

    // s are unique
    // z are unique
    // take advantage of this fact?

    // linked list?
    // vector<pair<int, int>> xs(n);

    pair<int, int> fst(0, 0);
    pair<int, int> snd(0, 0);

    int fst_sm = 0;
    int snd_sm = 0;

    for (int i = 0; i < n; ++i) {
        int s, z;
        cin >> s >> z;
        int sm = s + z;

        auto p = pair<int, int>(s, z);
        if (sm > fst_sm) {
            fst_sm = sm;
            fst = p;
        } else if (sm > snd_sm) {
            snd_sm = sm;
            snd = p;
        }
    }

    // cout << "FIRST : " << fst.first << "," << fst.second << "\n";
    // cout << "SECOND: " << snd.first << "," << snd.second << "\n";

    bool fst_gone = (fst.first < snd.first) || (fst.second < snd.second);
    bool snd_gone = (snd.first < fst.first) || (snd.second < fst.second);

    // cerr << "FIRST: " << fst.first << " " << fst.second << " gone? " << fst_gone << "\n";
    // cerr << "SECND: " << snd.first << " " << snd.second << " gone? " << snd_gone << "\n";

    if (fst_gone && snd_gone) {
        cout << "TAK\n";
    } else {
        cout << "NIE\n";
    }

/*
    while (!xs.empty()) {
        if (xs.size() == 1) {
            cout << "NIE\n";
            return 0;
        }

        auto [s0, z0] = xs[0];
        auto [s1, z1] = xs[1];

        bool remove0 = (s0 < s1) || (z0 < z1);
        bool remove1 = (s1 < s0) || (z1 < z0);
        if (remove0) {
            xs.erase(xs.begin());
            if (remove1) {
                xs.erase(xs.begin());
            }
        } else if (remove1) {
            xs.erase(xs.begin() + 1);
        }
    }

    cout << "TAK\n";
*/

/*
    for (auto [s, z]: xs) {
        cout << s << " " << z << "\n";
    }
*/

    return 0;
}
