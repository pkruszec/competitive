#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>

using namespace std;

vector<vector<int>> l;
vector<vector<int>> v;

int s, d;

vector<pair<int, int>> ds = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
int search(int y, int x, int i)
{
    int m = l[y][x];


    queue<pair<int, int>> q;
    q.push({x, y});
    v[y][x] = i;
    int c = 1;
    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();

        for (auto [dx, dy]: ds) {
            int nx = cx+dx;
            int ny = cy+dy;
            if (v[ny][nx] >= i) continue;
            if (l[ny][nx] > m) continue;
            v[ny][nx] = i;

            q.push({nx, ny});
            c++;

            if (c >= d) return c;
        }
    }

    return c;
}

// This is a directed graph.
// Make a directed graph, then maybe divide it into strongly connected components.
// Work on that.

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> s >> d;
    l.resize(s+2, vector<int>(s+2, INT_MAX));
    v.resize(s+2, vector<int>(s+2, INT_MAX));

    vector<pair<int, int>> p;
    for (int i = 1; i <= s; ++i) {
        for (int j = 1; j <= s; ++j) {
            cin >> l[i][j];
            v[i][j] = 0;
            p.push_back({i, j});
        }
    }

    sort(p.begin(), p.end(), [&](auto a, auto b) -> bool {
        int ax = l[a.first][a.second];
        int bx = l[b.first][b.second];
        return ax < bx;
    });

    int it = 1;
    for (auto [i, j]: p) {
        if (v[i][j] != 0) continue;

        int c = search(i, j, it++);
        if (c < d) continue;
        int m = l[i][j];
        cout << m << "\n";
        return 0;
    }

    /*
    int m = INT_MAX;
    int it = 1;
    for (int i = 1; i <= s; ++i) {
        for (int j = 1; j <= s; ++j) {
            if (l[i][j] >= m) continue;
            int c = search(i, j, it++);
            if (c < d) continue;
            m = l[i][j];
        }
    }
    cout << m << "\n";
    */

    return 0;
}
