//
// Walki robotów (wal)
// Paweł Kruszec
// solved (100)
//

#include <iostream>
#include <vector>
#include <stdint.h>
#include <limits.h>
#include <queue>
#include <bitset>
#include <algorithm>

using namespace std;

using P = pair<int, int>;


bool all_done(vector<P> &p, int start_idx)
{
    /*
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
*/

    vector<bool> done(p.size());

    for (int it = 0; it < p.size(); ++it) {
        int i = (start_idx+it) % p.size();

        if (done[i]) continue;
        int b = 0;
        int v = INT_MAX;
        for (int j = 0; j < p.size(); ++j) {
            if (done[i]) continue;
            if (i==j) continue;
            int a = abs(p[i].first - p[j].second);
            if (a < v) {
                v = a;
                b = j;
            }
        }

        bool fst_done = p[i].first < p[b].first;
        bool snd_done = p[b].second < p[i].second;
        if (snd_done) {
            done[b] = true;
        }
        if (fst_done) done[i] = true;
    }

    bool all = true;
    for (int i = 0; i < p.size(); ++i) {
        if (!done[i]) {
            all = false;
            break;
        }
    }

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

    // int done_count = 0;
    // vector<bool> done(n, false);

#ifdef BIGTEST
    if (n == 0) {
        cout << "TAK\n";
        return 0;
    }
#endif

    if (n == 1) {
        cout << "NIE\n";
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        int s, z;
        cin >> s >> z;
        #ifdef BIGTEST
        s += 1;
        z += 1;
        #endif

        auto p = pair<int, int>(s, z);
        xs[i] = p;
    }

    sort(xs.begin(), xs.end(), [](auto a, auto b) {
        return a.first+a.second > b.first+b.second;
    });

    int count = 1;
    for (int i = 1; i < n; ++i) {
        if (xs[i].first + xs[i].second != xs[0].first + xs[0].second) break;
        count++;
    }

    if (count % 2 == 0) {
        cout << "TAK\n";
        return 0;
    }

    for (int i = count; i < n; ++i) {
        if (xs[i].first > xs[0].first || xs[i].second > xs[0].second) {
            cout << "TAK\n";
            return 0;
        }
    }

    cout << "NIE\n";

    // if (elim) {
    //     cout << "TAK\n";
    // } else {
    //     cout << "NIE\n";
    // }

    // vector<P> p {fst_s, fst_z, snd_s, snd_z};

    // TODO: duel fst_s and fst_z, snd_s and snd_z

/*
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
*/

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
