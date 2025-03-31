#include <iostream>
#include <vector>
#include <algorithm>

typedef long long s64;

#define rep(n, i) for (auto i = 0; i < n; ++i)

using namespace std;

s64 n, k, m;
vector<s64> dist;

s64 next(int i)
{
    rep(n, j) {
        if (i==j) continue;

        s64 d = abs(dist[i]-dist[j]);
        s64 count = 0;
        s64 count_eq = 0;
        rep(n, a) {
            s64 d2 = abs(dist[i]-dist[a]);
            if (d2 <= d) {
                count++;
            }
            if (d2 == d) {
                count_eq++;
            }
        }
        s64 count_less = count - count_eq;

        if (count_less <= k && count > k) {
            return j;
        }
    }
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k >> m;
    dist.resize(n);
    
    vector<int> cache(n);

    rep(n, i) {
        cin >> dist[i];
    }

    rep(n, i) {
        cache[i] = next(i);
    }

    rep(n, i) {
        int j = i;
        rep(m, x) {
            j = cache[j];
        }
        cout << (j+1) << " ";
    }
    cout << "\n";

    return 0;
}
