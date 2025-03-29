#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> colors;

void color(int v)
{
    if (colors[v] == 0) {
        colors[v] = 1;
    }
    int opp = colors[v] == 1 ? 2 : 1;

    for (auto w: graph[v]) {
        if (colors[w] != 0) continue;
        colors[w] = opp;
        color(w);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    graph.resize(n + 1);
    colors.resize(n + 1);

    for (int i = 0; i < m; ++i) {
        int v, w;
        cin >> v >> w;

        graph[v].push_back(w);
        graph[w].push_back(v);
    }

    color(1);

    for (int v = 1; v <= n; ++v) {
        if (colors[v] == 0) {
            cout << "0\n";
            return 0;
        }

        for (auto w: graph[v]) {
            if (colors[v] == colors[w]) {
                cout << "0\n";
                return 0;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << i << ": " << colors[i] << "\n";
    }

    return 0;
}

/*
 - Always multiply solution by 2, because we can flip.

 If we had no connections, the number of possible states would be
 r! * b!

 But we need to take into account that connections cannot cross.

*/