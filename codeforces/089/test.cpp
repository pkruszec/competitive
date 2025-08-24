#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

#define N (10000010)

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> xs(n);
    for (int i = 0; i < n; ++i) {
        cin >> xs[i];
    }

    vector<int> fact(N, 0);
    fact[1] = 1;

    for (int i = 2; i < N; ++i) {
        if (fact[i] == 0) {
            fact[i] = i;
            for (int j = i; j < N; j += i) {
                if (fact[j] == 0) fact[j] = i;
            }
        }
    }

    vector<int> p0(n, -1);
    vector<int> p1(n, -1);

    for (int it = 0; it < n; ++it) {
        int x = xs[it];
        vector<int> p;

        int y = x;
        while (y > 1) {
            int idx = -1;
            for (int i = 0; i < p.size(); ++i) {
                if (p[i] == fact[y])
                {
                    idx = i;
                    break;
                }
            }

            if (idx == -1) {
                p.push_back(fact[y]);
            } else {
                //p[idx] *= fact[y];
            }

            y /= fact[y];
        }

        if (p.size() == 1) {
            continue;
        }

        int a = 1;
        int b = 1;
        int m = p.size() / 2;

        // cout << x << ": ";
        // for (auto d: p) {
        //     cout << d << ' ';
        // }
        // cout << '\n';
        // cout << "    " << 0 << " to < " << m << "\n";
        // cout << "    " << m << " to < " << p.size() << "\n";

        for (int i = 0; i < m; ++i) {
            a *= p[i];
        }

        for (int i = m; i < p.size(); ++i) {
            b *= p[i];
        }

        p0[it] = a;
        p1[it] = b;
    }

    for (auto x: p0) {
        cout << x << ' ';
    }
    cout << '\n';

    for (auto x: p1) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}
/*
Znaleźć takie 2 dzielniki x, że ich suma nie ma wspólnych dzielników większych od 1.
*/
