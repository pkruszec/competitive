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
    int n, m;
    cin >> n >> m;

    vector<int> k(n);
    vector<int> w(m);

    for (int i = 0; i < n; ++i) {
        cin >> k[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> w[i];
    }

    int last = w.back();
    w.pop_back();

    if (last > k[0]) {
        cout << "0\n";
        return 0;
    }

    int mx = 0;
    int imx = 0;
    for (int i = 0; i < w.size(); ++i) {
        int x = w[i];
        // cout << x << "\n";
        if (x > mx) {
            mx = x;
            imx = i;
        }
    }

    
    int md = n-1;
    for (int i = 0; i < n; ++i) {
        if (mx > k[i]) {
            md = i-1;
            break;
        }
    }

    int mh = md - (w.size() - 1 - imx) - 1;

    int dh = n-1;
    for (int i = 0; i < n; ++i) {
        // cout << "i=" << i << "k="<< k[i] << "\n";
        if (last > k[i]) {
            dh = i-1;
            break;
        }
    }

    // cout << (w.size() - 1 - imx) << "  " << mh << "," << dh << "\n";

    int h = std::min(mh, dh);
    if (h < 0) {
        cout << "0\n";
        return 0;
    }

    cout << h+1 << "\n";

    // cout << mh << "," << dh << "\n";
    // int mh = std::max(md, (int)w.size());
    // cout << "mh: "<< mh << "\n";

    return 0;
}
