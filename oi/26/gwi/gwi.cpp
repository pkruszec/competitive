#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, r;
    cin >> n >> r;
    r -= 1;
    vector<int> l(n - 1);
    vector<int> p(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> l[i] >> p[i];
    }

    int c = 0;
    vector<int> t;
    vector<int> v(n, false);
    v[r] = true;
    t.push_back(r);

    bool left = l[0] < p[0];
    int j = 0;
    int s = 1;
    for (int i = 1; i < n-1; ++i) {
        if (l[i] < p[i] != left) break;
        s++;
    }
    cout << "s=" << s << "\n";
    if (left) {
        if (s <= r) {
            int m = r-s;
            for (r--; r >= m; r--) {
                v[r] = true;
                t.push_back(r);
                c += l[j++];
            }
        }
    } else {
        if (r+s < n) {
            int m = r+s;
            for (r++; r <= m; r++) {
                v[r] = true;
                t.push_back(r);
                c += p[j++];
            }
        }
    }

    for (auto x: v) {
        cout << x << " ";
    }
    cout << "\n";

    cout << c << "\n";
    for (auto x: t) {
        cout << x+1 << " ";
    }
    cout << "\n";

    return 0;
}
