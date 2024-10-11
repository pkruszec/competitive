#include <iostream>
#include <vector>

using namespace std;

int n;
int idx = 0;
vector<vector<char>> k;
vector<vector<int>> vis;

int dfs(int x, int y)
{
    // cout << x << "," << y << "\n";
    
    int c = 0;
    // TODO: vector bad here
    vector<pair<int, int>> pairs {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    };
    for (auto &p: pairs) {
        int nx = x + p.first;
        int ny = y + p.second;
        
        if(vis[ny][nx] > 0) continue;
        vis[ny][nx]++;
        
        if (k[ny][nx] == '.') {
            c += dfs(nx, ny);
        } else {
            // cout << k[ny][nx] << " " << nx << "," << ny << "\n";
            c++;
        }
        
    }
    
    return c;
}

int main()
{
    cin >> n;
    k.resize(n + 2, vector<char>(n + 2, '#'));
    vis.resize(n + 2, vector<int>(n + 2, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> k[i][j];
        }
    }
    
#if 0
    cout << dfs(2, 2) << "\n";
    for (int i = 0; i <= n+1; ++i) {
        for (int j = 0; j <= n+1; ++j) {
            cout << (vis[i][j] ? k[i][j] : ' ');
        }
        cout << "\n";
    }
#endif
    
    for (idx = 0; idx < n; ++idx) {
        int x, y;
        cin >> x >> y;
        
        for (int a = 0; a <= n+1; ++a) {
            for (int b = 0; b <= n+1; ++b) {
                vis[a][b] = 0;
            }
        }
        
        cout << dfs(y, x) << "\n";
    }
    
    return 0;
}
