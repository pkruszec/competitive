#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> edges;
vector<int> status;
vector<int> levels;
vector<bool> visited;

/*
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
*/

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

void set(int v, int w)
{
    if (status[v] != 0) return;
    if (status[w] == 1) { status[v] = 2; return; }
    status[v] = 1;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    status.resize(n+1, 0);
    visited.resize(n+1, 0);
    levels.resize(n+1, 0);
    edges.resize(m + 1, pair<int, int>(0, 0));

    for (int i = 1; i <= m; ++i) {
        cin >> edges[i].first >> edges[i].second;

        levels[edges[i].first]++;
        levels[edges[i].second]++;
    }

    for (int i = 1; i <= n; ++i) {
        if (levels[i] == 0) {
            cout << "NIE\n";
            return 0;
        }
    }

    for (int i = 1; i <= m; ++i) {
        int v = edges[i].first;
        int w = edges[i].second;

        set(v, w);
        set(w, v);
    }

    cout << "TAK\n";
    for (int i = 1; i <= n; ++i) {
        int s = status[i];
        cout << "NKS"[s] << "\n";
    }

    return 0;
}
