// https://codeforces.com/problemset/problem/519/B
// Paweł Kruszec <pakruszec@gmail.com>

#include <iostream>
#include <set>
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

    multiset<int> fst, snd, thd;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        fst.insert(x);
    }

    for (int i = 0; i < n-1; ++i) {
        int x;
        cin >> x;
        snd.insert(x);
    }

    for (int i = 0; i < n-2; ++i) {
        int x;
        cin >> x;
        thd.insert(x);
    }

    vector<int> diff1, diff2;
    set_difference(fst.begin(), fst.end(), snd.begin(), snd.end(),
                   inserter(diff1, diff1.begin()));
    set_difference(snd.begin(), snd.end(), thd.begin(), thd.end(),
                   inserter(diff2, diff2.begin()));

    for (auto x: diff1) {
        cout << x << " ";
    }
    cout << "\n";

    for (auto x: diff2) {
        cout << x << " ";
    }
    cout << "\n";

    return 0;
}
