#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int n;

vector<int> px {
    1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29
};

void gen(vector<pair<int, int>> &xs, int j, int mp, int c, int l)
{
    xs.push_back({c, l});
    for (int i = 1; i <= mp; ++i) {
        auto &p = px[j];
        if (p > (n/c)) return;
        c *= p;
        gen(xs, j+1, i, c, l * (i + 1));
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;

    vector<pair<int, int>> xs;
    gen(xs, 1, 31, 1, 1);

    sort(xs.begin(), xs.end());

    int max = 0;
    int best = 0;
    for (auto [x, l]: xs) {
        if (l > max) {
            max = l;
            best = x;
        }
    }

    cout << best << "\n";
    return 0;
}
