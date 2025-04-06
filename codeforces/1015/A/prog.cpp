#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

unordered_map<int, bool> printed;

void perm(int k, int i, vector<int> p)
{
    if (printed[k]) return;

    if (i > k) {
        if (p.size() != k) return;
        for (auto x: p) {
            cout << x << " ";
        }
        cout << "\n";

        printed[k] = true;

        return;
    }

    if (i == 1) {
        for (int j = 1; j <= k; ++j) {
            perm(k, i+1, {j});
        }
        return;
    }

    for (int j = 1; j <= k; ++j) {
        bool ok = (max(p[i-1-1], j) % i) == (i-1);
        if (find(p.begin(), p.end(), j) == p.end() && ok) {
            p.push_back(j);
            perm(k, i+1, p);
            p.pop_back();
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
        perm(k, 1, {});
        if (!printed[k]) {
            cout << "-1\n";
        }
    }
    return 0;
}
