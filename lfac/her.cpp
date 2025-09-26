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

    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;

        if (c == 'H') {
            h[i] = true;
        }
    }

    double mh = 0.0;
    double md = 0.0;

    double ch = 0.5;
    double cd = 0.5;

    for (auto x: h) {
        double dh = ch * 0.5;
        double dd = cd * 0.5;

        mh += dh;
        md += dd;
        ch -= dh;
        cd -= dd;

        if (x) {
            ch += 1.0 - (ch+cd);
        } else {
            cd += 1.0 - (ch+cd);
        }
    }

    if (abs(mh - md) < 0.1) {
        cout << "HM\n";
    } else if (mh > md) {
        cout << "H\n";
    } else {
        cout << "M\n";
    }

    // cout << "drank: " << mh << " h, " << md << " d\n";

    return 0;
}
