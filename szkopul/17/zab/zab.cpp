#include <iostream>
#include <vector>
#include <algorithm>

typedef long long s64;

#define rep(n, i) for (auto i = 0; i < n; ++i)

using namespace std;

s64 n, k, m;
vector<s64> dist;
vector<s64> cache;

#if 0
s64 next(s64 i)
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
#endif

void next2()
{
    s64 a=1;
    cache[1] = k + 1;
    for (int i = 2; i <= n; ++i) {
        while (a+k+1 <= n && dist[a+k+1] - dist[i] < dist[i] - dist[a]) {
            a++;
        }
        if (dist[i] - dist[a] >= dist[a+k] - dist[i]) {
            cache[i] = a;
        } else {
            cache[i] = a+k;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k >> m;
    dist.resize(n+1);
    cache.resize(n+1);

    for(int i = 1; i <= n; ++i) {
        cin >> dist[i];
    }

    next2();
    // rep(n, i) {
    //     cache[i] = next(i);
    // }

    for (int i = 1; i <= n; ++i) {
        int j = i;
        for (int x = 0; x < m; ++x) {
            j = cache[j];
        }
        cout << (j) << " ";
    }
    cout << "\n";

    return 0;
}
