#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<pair<int, int>> ds = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool check(vector<vector<int>> &f, int N, int K, int max) {
    vector<vector<bool>> visited(N, vector<bool>(N, false));

    auto ok = [&](int x, int y) {
        return x >= 0 && x < N && y >= 0 && y < N;
    };

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (f[i][j] <= max && !visited[i][j]) {
                queue<pair<int, int>> q;
                q.push({i, j});
                visited[i][j] = true;

                int area = 0;

                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    area++;

                    if (area >= K) {
                        return true;
                    }

                    for (auto &[dx, dy] : ds) {
                        int nx = x + dx;
                        int ny = y + dy;
                        if (ok(nx, ny) && !visited[nx][ny] && f[nx][ny] <= max) {
                            visited[nx][ny] = true;
                            q.push({nx, ny});
                        }
                    }
                }
            }
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N, K;
    cin >> N >> K;

    vector<vector<int>> f(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> f[i][j];
        }
    }

    int left = 0, right = 1e9, result = -1;
    while (left <= right) {
        int mid = (left + right) / 2;

        if (check(f, N, K, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << result << endl;

    return 0;
}
