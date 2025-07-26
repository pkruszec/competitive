#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    vector<int> a(n);
    vector<int> b(n);

    for(int i = 0; i < n; ++i)
        cin >> a[i];
    for(int i = 0; i < n; ++i)
        cin >> b[i];

    long long g = 0;
    vector<int> t;

    for(int i = 0; i < n; ++i)
    {
        long long f = bgn[i] - end[i];
        g += f;
        if(f != 0)
        {
            t.push_back();
        }
    }

    

    cout << t << "\n";

    return 0;
}
