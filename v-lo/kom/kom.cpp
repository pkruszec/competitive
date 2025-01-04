#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

int n;
vector<vector<char>> k;

vector<pair<int, int>> dir {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// struct PH {
//     template<typename T, typename U>
//     size_t operator()(const pair<T, U> &p) const
//     {
//         return hash<T>()(p.first) ^ hash<U>()(p.second);
//     }
// };
// unordered_map<pair<int, int>, int, PH> ss;

vector<vector<int>> ss;
vector<int> wc(1);
int cs = 0;

int check(int x, int y)
{
    if (ss[y][x] > 0) {
        return wc[ss[y][x]];
    }

    int iter = 0;
    queue<pair<int, int>> q;
    q.push({x, y});

    int s = ++cs;
    ss[y][x] = s;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        for (auto &dd: dir) {
            int nx = dd.first + p.first;
            int ny = dd.second + p.second;
            if (ss[ny][nx] > 0) continue;
            if (k[ny][nx] == '#') {
                iter++;
                continue;
            }

            ss[ny][nx] = s;
            q.push({nx, ny});
        }
    }

    wc.push_back(iter);
    // wc[s] = iter;

    return iter;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    k.resize(n + 2, vector<char>(n + 2, '#'));
    ss.resize(n + 2, vector<int>(n + 2, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> k[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> y >> x;
        cout << check(x, y) << "\n";
    }
    return 0;
}
