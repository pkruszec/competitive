//
// Walki robotów (wal)
// Paweł Kruszec
//

#include <iostream>
#include <vector>
#include <stdint.h>
#include <queue>
#include <algorithm>

using namespace std;

using P = pair<int, int>;

bool all_done(vector<P> &p, int start_idx)
{
    vector<bool> done(p.size());

    for (int it = 0; it < p.size(); ++it) {
        int i = (start_idx+it) % p.size();

        if (done[i]) continue;
        for (int j = 0; j < p.size(); ++j) {
            if (done[j]) continue;
            if (i == j) continue;

            bool fst_done = p[i].first < p[j].first;
            bool snd_done = p[j].second < p[i].second;

            if (fst_done && snd_done) {
                done[i] = true;
                done[j] = true;
                break;
            }

            // if (snd_done) {
            //     done[j] = true;
            // }

            // if (fst_done) {
            //     done[i] = true;
            //     break;
            // }
        }
    }

    bool all = true;
    for (int i = 0; i < p.size(); ++i) {
        if (!done[i]) {
            all = false;
            break;
        }
    }

    cout << start_idx << " ::(";
    for (int i = 0; i < p.size(); ++i) {
        cout << p[i].first << "," << p[i].second << "->" << done[i]<< " ";
    }
    cout << start_idx << ") ";
    return all;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<pair<int, int>> xs(n);
    // vector<bool> done(n);

#ifdef BIGTEST
    if (n == 0) {
        cout << "TAK\n";
        return 0;
    }
#endif

    for (int i = 0; i < n; ++i) {
        int s, z;
        cin >> s >> z;
        #if BIGTEST
        s += 1;
        z += 1;
        #endif

        auto p = pair<int, int>(s, z);
        xs[i] = p;
    }


    P fst_s = {};
    P fst_z = {};
    P snd_s = {};
    P snd_z = {};

    sort(xs.begin(), xs.end(), [](auto a, auto b){
        return a.first > b.first;
    });

    int s = 0;
    int i = 0;
    for (auto p: xs) {
        // if (i < 10) cout << "(" << p.first << "," << p.second << ") ";

        if (s == 0) {
            fst_s = p;
            s++;
        }
        else if (s == 1 && p != fst_s) {
            snd_s = p;
            s++;
        } else break;

        i++;
    }

    sort(xs.begin(), xs.end(), [](auto a, auto b){
        return a.second > b.second;
    });

    s = 0;
    for (auto p: xs) {
        if (p == fst_s || p == snd_s) continue;
        if (s == 0) {
            fst_z = p;
            s++;
        }
        else if (s == 1 && p != fst_z) {
            snd_z = p;
            s++;
        } else break;
    }

    bool s_elim = fst_s.second < snd_s.second;
    bool z_elim = fst_z.first < snd_z.first;

    if (s_elim && z_elim) {
        cout << "TAK\n";
        return 0;
    }

    vector<P> p {fst_s, fst_z, snd_s, snd_z};
    
    bool all = false;
    for (int i = 0; i < p.size(); ++i) {
        if (all_done(p, i)) {
            all = true;
            break;
        }
    }    

    if (all) {
        cout << "TAK\n";
    } else {
        cout << "NIE\n";
    }

/*
    if ((s_elim && !z_elim) || (z_elim && !s_elim)) {
        cout << "FST_S: " << fst_s.first << "," << fst_s.second << "\n";
        cout << "SND_S: " << snd_s.first << "," << snd_s.second << "\n";
        cout << "FST_Z: " << fst_z.first << "," << fst_z.second << "\n";
        cout << "SND_Z: " << snd_z.first << "," << snd_z.second << "\n";
        cout << "NIE\n";
        return 0;
    }
*/

/*
    bool elim = 
        (fst_s.first > fst_z.first && fst_s.second < fst_z.second) ||
        (fst_s.first < fst_z.first && fst_s.second > fst_z.second);

    if (elim) {
        cout << "TAK\n";
    } else {
        cout << "FST_S: " << fst_s.first << "," << fst_s.second << "\n";
        cout << "FST_Z: " << fst_z.first << "," << fst_z.second << "\n";

        // cout << "SND_S: " << snd_s.first << "," << snd_s.second << "\n";
        // cout << "SND_Z: " << snd_z.first << "," << snd_z.second << "\n";
        cout << "NIE\n";
    }
*/    

/*
    for (int i = 0; i < n; ++i) {
        if (done[i]) continue;
        for (int j = 0; j < n; ++j) {
            if (done[j]) continue;
            if (i == j) continue;

            bool fst_done = xs[i].first < xs[j].first;
            bool snd_done = xs[j].second < xs[i].second;

            if (fst_done && snd_done) {
                done[i] = true;
                done[j] = true;
                break;
            }
        }
    }

    bool all = true;
    for (int i = 0; i < n; ++i) {
        // cout << done[i] << " ";
        if (!done[i]) {
            all = false;
            break;
        }
    }

    if (all) {
        cout << "TAK\n";
    } else {
        cout << "NIE\n";
    }
*/

    return 0;
}
