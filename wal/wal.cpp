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

        if (s > fst_s.first) {
            snd_s = fst_s;
            fst_s.first = s;
            fst_s.second = z;
        } else if (s > snd_s.first) {
            snd_s.first = s;
            snd_s.second = z;
        }

        if (z > fst_z.second) {
            snd_z = fst_z;
            fst_z.first = s;
            fst_z.second = z;
        } else if (z > snd_z.second) {
            snd_z.first = s;
            snd_z.second = z;
        }
    }

    // cout << "FIRST  S: " << fst_s.first << ", " << fst_s.second << "\n";
    // cout << "SECOND S: " << snd_s.first << ", " << snd_s.second << "\n";
    // cout << "FIRST  Z: " << fst_z.first << ", " << fst_z.second << "\n";
    // cout << "SECOND Z: " << snd_z.first << ", " << snd_z.second << "\n";

    bool s_good = (fst_s.second < snd_s.second);
    bool z_good = (fst_z.first < snd_z.first);
    if (s_good && z_good) {
        cout << "TAK\n";
    } else {
        cout << "NIE\n";
    }

    return 0;
}
