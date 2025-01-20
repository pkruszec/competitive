// https://codeforces.com/problemset/problem/2050/As
// Paweł Kruszec <pakruszec@gmail.com>

#include <iostream>
#include <string>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        int wc = 0;
        int acc = 0;
        while (n--) {
            string s;
            cin >> s;
            acc += s.size();

            if (acc > m) continue;
            wc++;
        }

        cout << wc << "\n";
    }
    return 0;
}
