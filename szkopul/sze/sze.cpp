#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    vector<float> a(n);
    vector<float> b(n);

    vector<int> k(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
        k[i] = i;
    }

    sort(k.begin(), k.end(), [&](auto i, auto j) {
        float ajbi = a[j] * b[i];
        float aibj = a[i] * b[j];
        bool l = (ajbi < aibj) || (ajbi == aibj && i < j);
        return l;
    });

    for (auto x: k) {
        cout << x+1 << "\n";
    }

    return 0;
}
