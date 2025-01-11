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

using G = vector<vector<vector<pair<int, int>>>>;

G make_digraph()
{
    G graph(s+2, vector<vector<pair<int, int>>>(s+2));

    for (int i = 1; i <= s; ++i) {
        for (int j = 1; j <= s; ++j) {
            for (auto [dx, dy]: ds) {
                int ny = i+dy;
                int nx = j+dx;
                if (l[ny][nx] <= l[i][j]) graph[i][j].push_back({ny, nx});
            }
        }
    }

    return graph;
}

int search(G &g, int y, int x, int it)
{
    // cout << x << "," << y << "\n";

    int m = l[y][x];

    queue<pair<int, int>> q;
    q.push({y, x});
    v[y][x] = it;

    int c = 1;
    while (!q.empty()) {
        auto [cy, cx] = q.front();
        q.pop();

        for (auto [ny, nx]: g[cy][cx]) {
            if (v[ny][nx] >= it) continue;
            v[ny][nx] = it;
            q.push({ny, nx});
            c++;
        }

        for (auto [dx, dy]: ds) {
            int nx = cx+dx;
            int ny = cy+dy;

            if (v[ny][nx] >= it) continue;
            if (l[ny][nx] > m) continue;
            v[ny][nx] = it;

            //cout<< "--- " << nx << "," << ny << " " << m << "\n";
            c += search(g, ny, nx, it);
        }
    }
    return c;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> s >> d;
    l.resize(s+2, vector<int>(s+2, INT_MAX));
    v.resize(s+2, vector<int>(s+2, INT_MAX));

    for (int i = 1; i <= s; ++i) {
        for (int j = 1; j <= s; ++j) {
            cin >> l[i][j];
            v[i][j] = 0;
        }
    }

    G graph = make_digraph();

    int m = INT_MAX;
    int it = 1;
    for (int i = 1; i <= s; ++i) {
        for (int j = 1; j <= s; ++j) {
            if (l[i][j] >= m) continue;
            int count = search(graph, i, j, it++);
            // cout << j << "," << i << "(" << l[i][j] << ") -> " << count << "\n";
            if (count < d) continue;
            m = l[i][j];
        }
    }

    cout << m << "\n";

    // cout << "digraph {\n";
    // for (int i = 1; i <= s; ++i) {
    //     for (int j = 1; j <= s; ++j) {
    //         cout << '"' << j << "," << i << "("<< l[i][j] << ")" << '"' << " -> {";
    //         for (auto [y, x]: graph[i][j]) {
    //             cout << '"' << x << "," << y << "("<< l[y][x] << ")" << '"' << " ";
    //         }
    //         cout << "}\n";
    //     }
    // }
    // cout << "}\n";

    return 0;
}
