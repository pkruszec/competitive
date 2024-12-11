#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <algorithm>
#include <limits.h>

using namespace std;

#ifdef PERF
uint64_t p0 = 0;
uint64_t p1 = 0;

# define PerfBegin() do {p0 = __rdtsc();} while (0)
# define PerfEnd()   do {p1 = __rdtsc(); cout << "CycleCount: " << p1-p0 << "\n";} while (0)
#else
# define PerfBegin()
# define PerfEnd()
#endif

int n, d;
vector<vector<int>> a;

// things reset
int iter = 0;
vector<vector<bool>> vis;

vector<pair<int, int>> dir = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1},
};

void check(int x, int y, int target)
{
    queue<pair<int, int>> q;
    q.push({x, y});
    iter++;
    vis[y][x] = true;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        for (auto &dd: dir) {
            int nx = dd.first + p.first;
            int ny = dd.second + p.second;
            if (vis[ny][nx]) continue;
            if (a[ny][nx] <= 0) continue;
            if (a[ny][nx] > target) continue;
            if (iter >= d) return;

            q.push({nx, ny});
            iter++;
            vis[ny][nx] = true;
        }
    }
}

void clear(int x, int y)
{
    if (!vis[y][x]) return;

    queue<pair<int, int>> q;
    q.push({x, y});

    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        vis[p.second][p.first] = false;

        for (auto &dd: dir) {
            int nx = dd.first + p.first;
            int ny = dd.second + p.second;
            if (!vis[ny][nx]) continue;
            if (a[ny][nx] <= 0) continue;

            vis[ny][nx] = false;
            q.push({nx, ny});
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> d;
    a.resize(n+2, vector<int>(n+2, INT_MIN));
    vis.resize(n+2, vector<bool>(n+2, false));
    vector<pair<int, int>> ps;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
            ps.push_back({j, i});
        }
    }

    sort(ps.begin(), ps.end(), [](auto p0, auto p1) {
        return a[p0.second][p0.first] < a[p1.second][p1.first];
    });

    int count = 0;

    for (auto &p: ps) {
        count++;

        // TODO: reset using bfs?
        // for (int y = 0; y <= n+1; ++y) {
        //     for (int x = 0; x <= n+1; ++x) {
        //         vis[y][x] = false;
        //     }
        // }

        iter = 0;
        int i = p.second;
        int j = p.first;
        check(j, i, a[i][j]);
        if (iter >= d) {
            cerr << count << "\n";
            cout << a[i][j] << '\n';
            return 0;
        }

        clear(j, i);
    }

    // cout << "NIE\n";
    return 0;
}
