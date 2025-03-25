#include <iostream>
#include <vector>
#include <unordered_map>
#include <assert.h>

using namespace std;

struct Triangle {
    int a, b, c;
};

int main()
{
    int n;
    cin >> n;
    if (n < 6) {
        cout << n - 2 << "\n";
        return 0;
    }

    vector<Triangle> tri(n-2 + 1);
    unordered_map<int, unordered_map<int, pair<int, int>>> sides;
    vector<vector<int>> adj(n-2 + 1);

    auto _append = [&](int x, int y, int v) {
        if (sides[x][y].first == 0) {
            sides[x][y].first = v;
        } else if (sides[x][y].second == 0) {
            sides[x][y].second = v;
        } else {
            assert(false);
        }
    };

    auto append = [&](int x, int y, int v) {
        _append(x, y, v);
        _append(y, x, v);
    };

    for (int i = 1; i <= n-2; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        tri[i].a = a;
        tri[i].b = b;
        tri[i].c = c;

        append(a, b, i);
        append(a, c, i);
        append(b, c, i);
    }

    cout << "graph{\n";
    for (auto &p: sides) {
        for (auto &k: p.second) {
            auto &d = k.second;
            cout << d.first << " -- " << d.second << "\n";
        }
    }
    cout << "}\n";

    return 0;
}
