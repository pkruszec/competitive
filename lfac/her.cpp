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

    vector<bool> h(n, false);

    int nh = 0;
    int nm = 0;

    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;

        if (c == 'H') {
            h[i] = true;
            if (i != (n-1)) nh++;
        } else {
            if (i != (n-1)) nm++;
        }
    }

    if (n == 1) {
            cout << "HM\n";
    } else if (nh > nm) {
        cout << "H\n";
    } else if (nh < nm) {
        cout << "M\n";
    } else {
        if (h[n-2]) {
            cout << "M\n";
        } else {
            cout << "H\n";
        }
    }

    return 0;
}
