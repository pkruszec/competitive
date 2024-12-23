#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
vector<vector<char>> k;
// vector<vector<bool>> vis;

vector<pair<int, int>> dir {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int check(int x, int y)
{
    vector<vector<bool>> vis(n + 2, vector<bool>(n + 2, false));

    int iter = 0;
    queue<pair<int, int>> q;
    q.push({x, y});
    vis[y][x] = true;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        for (auto &dd: dir) {
            int nx = dd.first + p.first;
            int ny = dd.second + p.second;
            if (vis[ny][nx]) continue;
            if (k[ny][nx] == '#') {
                //cout << nx << "," << ny << "\n";
                iter++;
                continue;
            }

            q.push({nx, ny});
            vis[ny][nx] = true;
        }
    }

    return iter;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    k.resize(n + 2, vector<char>(n + 2, '#'));
    // vis.resize(n + 2, vector<bool>(n + 2, false));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> k[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> y >> x;

        // for (int i = 1; i < n+1; ++i) {
        //     for (int j = 1; j < n+1; ++j) {
        //         vis[i][j] = false;
        //     }
        // }

        cout << check(x, y) << "\n";
    }
    return 0;
}
