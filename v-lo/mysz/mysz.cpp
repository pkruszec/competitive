#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>

using namespace std;

using P = pair<int, int>;

int width, height;
vector<vector<char>> g;
vector<vector<bool>> vis;
vector<vector<int>> dist;
P o, w;

int bfs(int x, int y)
{
    queue<P> q;
    q.push(P(x, y));
    
    vis[y][x] = true;
    dist[y][x] = 1;
    vector<P> dix = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    int m = -1;
    while (!q.empty()) {
        auto [px, py] = q.front();
        // cout << px << "," << py << "\n";
        
        q.pop();
        if (px == w.first && py == w.second) return m;
        
        for (auto [dx, dy]: dix) {
            int nx = px + dx;
            int ny = py + dy;
            
            if (vis[ny][nx]) continue;
            if (g[ny][nx] == '-') {
                vis[ny][nx] = true;
                dist[ny][nx] = dist[py][px] + 1;
                q.push(P(nx, ny));
                
                if (dist[ny][nx] > m) m = dist[ny][nx];
            }
        }
    }
    
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> width;
    cin >> height;
    
    g.resize(height+2, vector<char>(width+2, 'x'));
    vis.resize(height+2, vector<bool>(width+2, false));
    dist.resize(height+2, vector<int>(width+2, 999));
    
    for (int i = 1; i <= height; ++i) {
        for (int j = 1; j <= width; ++j) {
            cin >> g[i][j];
            if (g[i][j] == 'w') {
                w = P(j, i);
                g[i][j] = '-';
            } else if (g[i][j] == 'o') {
                o = P(j, i);
                g[i][j] = '-';
            }
        }
    }
    
    int c = bfs(o.first, o.second);
    if (c >= 0)
        cout << c << '\n';
    else
        cout << "NIE\n";
    
#if 0
    for (int i = 0; i <= height+1; ++i) {
        for (int j = 0; j <= width+1; ++j) {
            cout << setw(4) << dist[i][j];
        }
        cout << "\n";
    }
#endif
    
    return 0;
}
