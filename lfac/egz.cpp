#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> path;

    int o = 1;

    while (path.size() < n) {
        int p = o;
        int last = p;
        while (1) {
            path.push_back(p);
            last = p;
            if (p + m <= n) {
                p += m;
            } else {
                break;
            }
        }

        if (m == 1) {
            break;
        }

        if (path.size() >= n) {
            break;
        }

        o++;
        if (abs(last - o) < m) {
            cout << "NIE\n";
            return 0;
        }
    }

    for (int x: path) {
        cout << x << " ";
    }
    cout << "\n";
    
    return 0;
}

