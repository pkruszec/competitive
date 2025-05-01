//
// Usuwanie (usu)
// Paweł Kruszec
// solved
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

    uint64_t lo, hi;
    cin >> lo >> hi;

    uint64_t d = hi-lo+1;

    if (d != 0 && ((d - 3) % 4 == 0)) {
        cout << d - 1 << '\n';
    } else {
        cout << d/4 * 4 << '\n';
    }

    // cout << lo << " " << hi << "\n";

/*
    vector<int> xs(hi - lo + 1);
    for (int i = 0; i < xs.size(); ++i) {
        xs[i] = lo+i;
    }

    uint64_t c = 0;
    while (xs.size() > 0) {
        int a = xs[0];
        int p = a % 2;

        int j = -1;
        for (int i = 1; i < xs.size(); ++i) {
            if (xs[i] % 2 == p) {
                j = i;
                break;
            }
        }
        // cout << a << "," << j << "," << p << '\n';

        if (j >= 0) {
            xs.erase(xs.begin() + j);
            xs.erase(xs.begin());
            c += 2;
        } else {
            break;
        }
    }

    // for(auto x: xs){
    //     cout << x << " ";
    // }
    // cout << "\n";

    cout << c << '\n';
*/

    return 0;
}
