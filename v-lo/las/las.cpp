#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

vector<vector<int>> l;
vector<vector<int>> v;

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
            // if (x == 3 && y == 2) cout << nx << "," << ny << " -> " << v[ny][nx] << "\n";
            if (v[ny][nx] >= i) continue;
            if (l[ny][nx] > m) continue;
            v[ny][nx] = i;

            q.push({nx, ny});
            c++;
        }
    }

    return c;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int s, d;
    cin >> s >> d;
    l.resize(s+2, vector<int>(s+2, INT_MAX));
    v.resize(s+2, vector<int>(s+2, INT_MAX));

    for (int i = 1; i <= s; ++i) {
        for (int j = 1; j <= s; ++j) {
            cin >> l[i][j];
            v[i][j] = 0;
        }
    }

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
    return 0;
}
