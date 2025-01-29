#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// struct H {
//     size_t operator()(const tuple<int, int, int> &x) const
//     {
//         return hash<int>()(get<0>(x)) ^ hash<int>()(get<1>(x)) ^ hash<int>()(get<2>(x));
//         // return hash<decltype(get<0>(x))>()(get<0>(x));
//     }
// };

unordered_map<int, vector<int>> e;
vector<tuple<int, int, int>> tri;

template<typename U, typename T>
bool has(U &xs, T x)
{
    return find(xs.begin(), xs.end(), x) != xs.end();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int p, k;
        cin >> p >> k;
        
        e[p].push_back(k);
        e[k].push_back(p);
    }

    // # one-color triangles = (# of triples of points that are all connected) + (# of triples of points that are all not connected)

    int red = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            if (!has(e[i], j)) continue;

            for (int k = 1; k <= n; ++k) {
                if (i == k) continue;
                if (j == k) continue;

                if (!has(e[i], k)) continue;
                if (!has(e[j], k)) continue;

                if (has(tri, tuple<int, int, int>{i, j, k})) continue;
                // if (has(tri, tuple<int, int, int>{i, k, j})) continue;
                // if (has(tri, tuple<int, int, int>{j, k, i})) continue;
                // if (has(tri, tuple<int, int, int>{j, i, k})) continue;
                // if (has(tri, tuple<int, int, int>{k, j, i})) continue;
                // if (has(tri, tuple<int, int, int>{k, i, j})) continue;

                red++;
                //tri.push_back({i, j, k});
                tri.push_back({i, j, k});
                tri.push_back({i, k, j});
                tri.push_back({j, k, i});
                tri.push_back({j, i, k});
                tri.push_back({k, j, i});
                tri.push_back({k, i, j});
            }
        }
    }

    int black = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            if (has(e[i], j)) continue;

            for (int k = 1; k <= n; ++k) {
                if (i == k) continue;
                if (j == k) continue;

                if (has(e[i], k)) continue;
                if (has(e[j], k)) continue;

                if (has(tri, tuple<int, int, int>{i, j, k})) continue;
                // if (has(tri, tuple<int, int, int>{i, k, j})) continue;
                // if (has(tri, tuple<int, int, int>{j, k, i})) continue;
                // if (has(tri, tuple<int, int, int>{j, i, k})) continue;
                // if (has(tri, tuple<int, int, int>{k, j, i})) continue;
                // if (has(tri, tuple<int, int, int>{k, i, j})) continue;

                black++;
                // tri.push_back({i, j, k});

                tri.push_back({i, j, k});
                tri.push_back({i, k, j});
                tri.push_back({j, k, i});
                tri.push_back({j, i, k});
                tri.push_back({k, j, i});
                tri.push_back({k, i, j});
            }
        }
    }

    cout << red + black << "\n";
    return 0;
}
