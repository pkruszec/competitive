#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct C
{
    int l, r, real;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;

    for(int i = 0; i < t; ++i)
    {
        int n, k;
        cin >> n >> k;
        vector<C> c(n, C{});
        for(int j = 0; j < n; ++j)
            cin >> c[j].l >> c[j].r >> c[j].real;

        sort(c.begin(), c.end(), [](auto x, auto y) -> bool {
            return x.l < y.l;
        });

        int cur = k;
        
        for(int i = 0; i < n; ++i)
        {
            if(c[i].l > cur) break;
            cur = max(cur, c[i].real);
        }

        cout << cur << "\n";
    }

    return 0;
}
