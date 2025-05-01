#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <limits.h>

using namespace std;

unordered_map<int, unordered_set<int>> gold;

int get(int y, int x) {
    return gold[y].find(x) != gold[y].end();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int s, w, n;
    cin >> s >> w >> n;

    int y_min = INT_MAX;
    int y_max = INT_MIN;
    int x_min = INT_MAX;
    int x_max = INT_MIN;

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        gold[y].insert(x);

        y_min = min(y_min, y);
        y_max = max(y_max, y);
        x_min = min(x_min, x);
        x_max = max(x_max, x);
    }

    int r = 0;
    for (int y = y_min; y <= y_max-w; ++y) {
        for (int x = x_min; x <= x_max-s; ++x) {
            //cout << x << "," << y << "\n";
            int m = 0;
            for (int i = 0; i < w; ++i) {
                for (int j = 0; j < s; ++j) {
                    m += get(y+i, x+j);
                }
            }

            r = max(r, m);
        }
    }

    cout << r << "\n";

    return 0;
}
