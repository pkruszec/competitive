#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <stdint.h>

using namespace std;

void f(int k)
{

    vector<bool> vis(k, false);
    queue<pair<int, pair<int, uint64_t>>> q;
    q.push({1, {0, 0}});
    vis[1] = true;

    while (!q.empty()) {
        auto &p = q.front();
        if (p.first == 0) {
            auto [c, o] = p.second;

            cout << "1";
            for (int i = 0; i < c; ++i) {
                cout << ((o >> i) & 1);
            }
            cout << "\n";
            return;
        }

        q.pop();

        int ten = p.first*10;
        int a = (ten)%k;
        int b = (ten + 1)%k;

        auto [c, o] = p.second;

        if (!vis[a]) {
            vis[a] = true;
            q.push({a, {c+1, o}});
        }

        if (!vis[b]) {
            vis[b] = true;
            q.push({b, {c+1, o | ((uint64_t)1 << c)}});
        }

    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        f(k);
    }
    
    return 0;
}
