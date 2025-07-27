#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, a, b;
    cin >> n >> m >> a >> b;

    float bp = (float)b / m;
    float ap = (float)a;

    int nm = n/m;
    int r = n % m;

    int c = 0;

    if(ap < bp)
    {
        c += n*a;
    }
    else
    {
        c += nm*b;
    }

    if(r*a < b)
    {
        c += r*a;
    }
    else
    {
        c += b;
    }

    cout << c << "\n";

    return 0;
}
