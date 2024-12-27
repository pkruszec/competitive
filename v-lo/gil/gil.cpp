#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> edges;
vector<int> status;
vector<bool> visited;

void fill(int v, int c=1)
{
    if (visited[v]) return;

    visited[v] = true;
    status[v] = c;

    for (auto &[a, b]: edges) {
        int w;
        if (a == v) {
            w = b;
        } else if (b ==v) {
            w = a;
        } else {
            continue;
        }
        if (visited[w]) continue;

        int nc = c == 1 ? 2 : 1;
        // cout << "fill_nc " << w << " " << nc << "\n";
        fill(w, nc);
    }
}

bool check(int v)
{
    bool k = status[v] == 1;
    bool s = status[v] == 2;

    for (auto &[a, b]: edges) {
        // if (v == 5) cout << a << " <-> " << b << " --- \n";

        int w;
        if (a == v) {
            w = b;
        } else if (b ==v) {
            w = a;
        } else {
            continue;
        }

        if (status[w] == 1) k = true;
        else if (status[w] == 2) s = true;


    }

    return k && s;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    if (m*2 < n) {
        cout << "NIE\n";
        return 0;
    }

    status.resize(n+1, 0);
    visited.resize(n+1, 0);
    edges.resize(m + 1, pair<int, int>(0, 0));

    for (int i = 1; i <= n; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) fill(i);
    }

    bool ok = true;

#if 1
    for (int i = 1; i <= n; ++i) {
        if (!check(i)) {
            // cout << i << " doesn't have\n";
            ok = false;
            break;
        }
    }
#endif

    if (ok) {
        cout << "TAK\n";
        for (int i = 1; i <= n; ++i) {
            int c = status[i];
            char xs[] = "NKS";
            cout << xs[c] << "\n";
        }
    } else {
        cout << "NIE\n";
    }

    return 0;
}
