#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<vector<bool>> m;

int right(int x)
{
    return (x+1)%n;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    m.resize(n, vector<bool>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c;
            cin >> c;
            m[i][j] = c == '1';
        }
    }

    vector<int> ok;

    for (int i = 0; i < n; ++i) {
        //cout << i+1 << "\n";

        bool valid = true;

        int j = i;
        int p = i;
        while (1) {
            j = right(j);
            if (j == i) break;

            if (!m[i][j]) {
                //cout << "  " << j+1 << "\n";

                bool ok = false;
                while (1) {
                    p = right(p);
                    if (p == j) break;

                    //cout << "    " << p << "\n";
                    if (m[p][j]) {
                        ok = true;
                        break;
                    }
                }

                if (!ok) {
                    valid = false;
                    break;
                }

                p = j;
            }
        }

        if (valid) {
            ok.push_back(i+1);
            //cout << "--- " << i+1 << " VALID!\n";
        }

        //break;
    }

    cout << ok.size() << "\n";
    for (auto x: ok) {
        cout << x << "\n";
    }

    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         cout << m[i][j];
    //     }
    //     cout << "\n";
    // }

    return 0;
}

/*
A > B
B > C
C > A

*/ 