#include <iostream>
#include <vector>
#include <algorithm>

typedef long long s64;

#define rep(n, i) for (auto i = 0; i < n; ++i)

using namespace std;

s64 n, k, m;
vector<s64> dist;
vector<s64> cache;

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

vector<int> r;

void f()
{
    for (int i = 1; i <= n; ++i) {
        r[i] = i;
    }

    auto g = cache;
    while (m > 0) {
        if (m%2 == 1) {
            auto h = r;
            for (int i = 1; i <= n; ++i) {
                r[i] = h[g[i]];
            }
        }
        m /= 2;
        auto h = g;
        for (int i = 1; i <= n; ++i) {
            g[i] = h[h[i]];
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
    r.resize(n+1);

    for(int i = 1; i <= n; ++i) {
        cin >> dist[i];
    }

    next2();
    // rep(n, i) {
    //     cache[i] = next(i);
    // }

    f();
    for (int i = 1; i <= n; ++i) {
        cout << r[i] << " ";
    }
    cout << "\n";

    return 0;
}
