#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct C
{
    int l, r, real;
    bool f;
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
            return x.real > y.real;
        });

        while(1)
        {
            bool ok = false;

            for(auto &x: c)
            {
                if(k >= x.l && k <= x.r && (x.real > k) && !x.f)
                {
                    k = x.real;
                    x.f = true;
                    ok = true;
                    break;
                }
            }   

            if(!ok) break;
        }

        cout << k << "\n";
    }

    return 0;
}
