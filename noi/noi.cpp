#include <iostream>
#include <vector>
#include <string>

#define BORDER 8

using namespace std;

int m, n;
vector<vector<int>> g;
vector<vector<bool>> vis;
vector<vector<bool>> conn;

vector<pair<int, int>> dir {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1},
};

int dfs(int y, int x)
{
    // cout << x << "," << y << "\n";
    vis[y][x] = true;
    for (auto &d: dir) {
        int nx = x + d.first;
        int ny = y + d.second;

        if (g[ny][nx] == 0) continue;
        if (g[ny][nx] == BORDER || conn[ny][nx]) {
            conn[y][x] = true;
            return 0;
        }
        
        if (vis[ny][nx]) continue;
        vis[ny][nx] = true;

        if (g[ny][nx] == 1) {
            if (dfs(ny, nx) == 0) {
                conn[ny][nx] = true;
                return 0;
            }
        }
    }

    return 1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> m >> n;
    g.resize(m+2, vector<int>(n+2, BORDER));
    vis.resize(m+2, vector<bool>(n+2, false));
    conn.resize(m+2, vector<bool>(n+2, false));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            char c;
            cin >> c;
            g[i][j] = c == 'l';
        }
    }

    int result = 0;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (g[i][j] == 1 && !vis[i][j]) {
                result += dfs(i, j);
                // cout << result << " <- " << j << " " << i << "\n";
            }
        }
    }

    cout << result << "\n";

    // for (int i = 0; i <= m+1; ++i) {
    //     for (int j = 0; j <= n+1; ++j) {
    //         cout << g[i][j];
    //     }
    //     cout << "\n";
    // }

    return 0;
}
