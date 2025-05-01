#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int n, m;
vector<int> p;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    srand(time(0));
    cin >> n >> m;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;

        int res = 0;

        unordered_set<int> had;
        for (int it = 0; it < 100; ++it) {
            int candidate = (rand()%n)+1;
            if (had.find(candidate) != had.end()) {
                it--;
                continue;
            }

            int count = 0;
            for (int i = l; i <= r; i++) {
                if (p[i] == candidate) {
                    count++;
                    if (count > (r-l+1) / 2) break;
                }
            }
            if (count > (r-l+1) / 2) {
                res = candidate;
                break;
            }
        }

        cout << res << "\n";
    }

    return 0;
}
