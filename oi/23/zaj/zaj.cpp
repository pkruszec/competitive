#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<int> N, M;
vector<vector<int>> Z;
vector<int> pa, pb;
vector<int> mem;

int nwz1()
{
    for (int i = 1; i <= n; ++i) {
        Z[i][0] = 0;
        for (int j = 1; j <= m; ++j) {
            if (N[i] == M[j] && pa[i] > 0 && pb[j] > 0) {
                Z[i][j] = Z[pa[i] - 1][pb[j] - 1] + 2;
            } else {
                Z[i][j] = 0;
            }
            Z[i][j] = max(Z[i][j], max(Z[i-1][j], Z[i][j-1]));
        }
    }
    return Z[n][m];
}

int nwz()
{
    for (int i = 1; i <= n; ++i) {
        Z[i%2][0] = 0;
        for (int j = 1; j <= m; ++j) {
            if (N[i] == M[j] && pa[i] > 0 && pb[j] > 0) {
                Z[i%2][j] = mem[pb[j]] + 2;
            } else {
                Z[i%2][j] = 0;
            }
            Z[i%2][j] = max(Z[i%2][j], max(Z[(i-1)%2][j], Z[i%2][j-1]));
        }
        for (int j = 1; j <= m; ++j) {
            if (N[i]==M[j]) mem[j] = Z[(i-1)%2][j-1];
        }
    }
    return Z[n%2][m];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    N.resize(n+1);
    M.resize(m+1);
    // Z.resize(n+1, vector<int>(m+1, 0));
    Z.resize(2, vector<int>(m+1, 0));
    pa.resize(n+1, 0);
    pb.resize(m+1, 0);
    mem.resize(m+1, 0);

    for (int i = 1; i <= n; ++i) cin >> N[i];
    for (int i = 1; i <= m; ++i) cin >> M[i];
    
    for (int i = 1; i <= n; ++i) {
        for (int j = i-1; j >= 0; --j) {
            if (N[i] == N[j]) {
                pa[i] = j;
                break;
            }
        }
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = i-1; j >= 0; --j) {
            if (M[i] == M[j]) {
                pb[i] = j;
                break;
            }
        }
    }

    cout << nwz() << "\n";

    return 0;
}
