//
// Walki robotów (wal)
// Paweł Kruszec
//

#include <iostream>
#include <vector>
#include <stdint.h>
#include <queue>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

#ifdef BIGTEST
    if (n == 0) {
        cout << "TAK\n";
        return 0;
    }
#endif

    // s are unique
    // z are unique
    // take advantage of this fact?

    pair<int, int> fst_s(0, 0);
    pair<int, int> snd_s(0, 0);
    pair<int, int> fst_z(0, 0);
    pair<int, int> snd_z(0, 0);

    for (int i = 0; i < n; ++i) {
        int s, z;
        cin >> s >> z;

#if BIGTEST
        s += 1;
        z += 1;
#endif

        if (s > fst_s.first || (s == fst_s.first && z > fst_s.second)) {
            snd_s = fst_s;
            fst_s.first = s;
            fst_s.second = z;
        } else if (s > snd_s.first || (s == snd_s.first && z > snd_s.second)) {
            snd_s.first = s;
            snd_s.second = z;
        }

        if (z > fst_z.second || (z == fst_z.second && s > fst_z.first)) {
            snd_z = fst_z;
            fst_z.first = s;
            fst_z.second = z;
        } else if (z > snd_z.second || (z == snd_z.second && s > snd_z.first)) {
            snd_z.first = s;
            snd_z.second = z;
        }
    }

    // Dumb Solution:
    // first, mark all excess duplicates dead

    bool dead[4] = {};
    pair<int, int> xs[4] = {fst_s, snd_s, fst_z, snd_z};

    for (int i = 0; i < 4; ++i) {
        if (dead[i]) continue;
        for (int j = 0; j < 4; ++j) {
            if (dead[j]) continue;
            if (j != i && xs[i] == xs[j]) {
                dead[j] = true;
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (dead[i]) continue;

        // try to find decisive opponent
        for (int j = 0; j < 4; ++j) {
            if (dead[j]) continue;
            if (j == i) continue;

            if (xs[i].first > xs[j].first && xs[i].second > xs[j].second) {
                dead[j] = true;
                // break;
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        cout << xs[i].first << "," << xs[i].second << " " << dead[i] << " ";
    }

    for (int i = 0; i < 4; ++i) {
        if (dead[i]) continue;
        for (int j = 0; j < 4; ++j) {
            if (dead[j]) continue;
            if (j == i) continue;
            dead[i] = true;
            dead[j] = true;
            break;
        }
    }

    bool all = true;
    for (int i = 0; i < 4; ++i) {
        if (!dead[i]) {
            all = false;
            break;
        }
        // cout << xs[i].first << "," << xs[i].second << " " << dead[i] << " ";
    }

    if (all) {
        cout << "TAK\n";
    } else {
        cout << "NIE\n";
    }

#if 0
    // fst_s.first is always greater than snd_s.first
    // fst_z.second is always greater than snd_s.second
    // If the first one doesn't win by the second attribute, they both die
    bool s_eliminated = (fst_s.second < snd_s.second);
    bool z_eliminated = (fst_z.first < snd_z.first);

    if (s_eliminated && z_eliminated) {
        cout << "TAK\n";
        return 0;
    }

    if ((s_eliminated && !z_eliminated) || (z_eliminated && !s_eliminated)) {
        cout << "FIRST  S: " << fst_s.first << ", " << fst_s.second << "\n";
        cout << "SECOND S: " << snd_s.first << ", " << snd_s.second << "\n";
        cout << "FIRST  Z: " << fst_z.first << ", " << fst_z.second << "\n";
        cout << "SECOND Z: " << snd_z.first << ", " << snd_z.second << "\n";
        cout << "NIE\n";
        return 0;
    }

    pair<int, int> s_best = fst_s;
    pair<int, int> z_best = fst_z;

    bool good = (
        ((s_best.first > z_best.first) && (s_best.second < z_best.second)) ||
        ((s_best.first < z_best.first) && (s_best.second > z_best.second))
    );

    if (good) {
        cout << "TAK\n";
    } else {
        cout << "NIE\n";
    }

#endif

    return 0;
}
