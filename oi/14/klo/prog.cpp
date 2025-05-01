#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int count(vector<int> &xs) {
    int c = 0;
    for (int i = 0; i < xs.size(); ++i) {
        if (i == xs[i]) c++;
    }
    return c;
}

int mc = 0;
vector<int> conf;

void search(vector<int> &xs, vector<int> &rem) {
    if (xs.size() <= mc) return;
    int c = count(xs);
    if (c > mc) {
        mc = c;
        conf = rem;
    }

    for (int i = 0; i < xs.size(); ++i) {
        vector<int> nxs = xs;
        vector<int> nrem = rem;
        nxs.erase(nxs.begin() + i);
        nrem.push_back(i);
        search(nxs, nrem);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    vector<int> xs(n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        x--;
        xs[i] = x;
    }

    vector<int> rem = {};
    search(xs, rem);

    cout << conf.size() << "\n";
    for (auto x: conf) cout << (x+1) << "\n";

    return 0;
}
