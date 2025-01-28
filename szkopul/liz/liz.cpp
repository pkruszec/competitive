#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;

vector<int> c;
vector<pair<int, int>> p;

void cache(int l, int r, int k)
{
    p[k] = {l, r};
    if (k >= 3) {
        if (c[l] == 2) {
            cache(l+1, r, k-2);
        } else if (c[r] == 2) {
            cache(l, r-1, k-2);
        } else {
            cache(l+1, r-1, k-2);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    
    c.resize(n+1);
    p.resize(n*2 + 1, {0, 0});

    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        char t;
        cin >> t;
        c[i] = (t == 'T' ? 2 : 1);    
        sum += c[i];
    }

    cache(1, n, sum);
    int l = -1;
    int r = -1;
    for (int i = 1; i <= n; ++i) {
        if (c[i] == 1) {
            if (l < 0) l = i;
            r = i;
        }
    }

    if (l != -1 && r-1 < n-l) {
        cache(l+1, n, sum - 2*(l-1) - 1);
    } else if (r != -1) {
        cache(1, r-1, sum - 2*(n-r) - 1);
    }

    for (int i = 0; i < k; ++i) {
        int cost;
        cin >> cost;
        if (cost > sum || p[cost] == pair<int,int>{0, 0}) {
            cout << "NIE\n";
        } else {
            cout << p[cost].first << " " << p[cost].second << "\n";
        }
    }

    return 0;
}
