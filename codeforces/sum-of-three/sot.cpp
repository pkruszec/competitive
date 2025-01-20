// https://codeforces.com/problemset/problem/1886/A
// Paweł Kruszec <pakruszec@gmail.com>

#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--) {
        int s;
        cin >> s;

        for (int i = 1; i <= s; ++i) {
            if (i % 3 == 0) continue;
            for (int j = 1; j <= s; ++j) {
                if (j % 3 == 0) continue;
                if (i == j) continue;


                int k = s - i - j;

                if (k < 1) continue;
                if (j == k) continue;
                if (i == k) continue;
                if (k % 3 == 0) continue;

                if (1) {
                   cout << "YES\n" << i << " " << j << " " << k << "\n";
                   goto next;
                }

                // for (int k = 1; k <= s; ++k) {
                //     if (k % 3 == 0) continue;
                //     if (j == k) continue;
                //     if (i == k) continue;
                    
                //     if (i+j+k == s) {
                //         cout << "YES\n" << i << " " << j << " " << k << "\n";
                //         goto next;
                //     }
                // }


            }
        }

        cout << "NO\n";
        next:;
    }
    return 0;
}
