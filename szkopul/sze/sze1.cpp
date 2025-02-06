#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <float.h>

using namespace std;

vector<float> a;
vector<float> b;

int n;

float h(int i, float t)
{
    return t*a[i] + b[i];
}

float cost(vector<int> &idx)
{
    float t = 0.0f;
    for (auto i: idx) {
        t += h(i, t);
    }
    return t;
}

vector<int> brute()
{
    queue<vector<int>> q;
    q.push({});

    vector<int> best;

    float mc = FLT_MAX;

    while (!q.empty()) {
        auto x = q.front();
        if (x.size() == n) {
            float c = cost(x);
            if (c < mc) {
                best = x;
                mc = c;
            }
        }
        q.pop();

        if (x.size() < n) {
            auto cp = x;
            for (int i = 0; i < n; ++i) {
                if (find(cp.begin(), cp.end(), i) != cp.end()) {
                    continue;
                }

                cp.push_back(i);
                q.push(cp);
                cp.pop_back();
            }
        }
    }

    return best;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;

    a.resize(n);
    b.resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
    }

    auto k = brute();

    for (auto x: k) {
        cout << x+1 << "\n";
    }

    // auto s = vector<int> {2, 4, 1, 5, 3};
    // cout << cost(s) << "\n";

    return 0;
}
