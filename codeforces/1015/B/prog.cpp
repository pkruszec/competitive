#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <string>
#include <queue>
#include <climits>

using namespace std;

long long gcd(long long a, long long b)
{
    while (a != b) {
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    return a;
}

bool is(unordered_set<long long> &v)
{
    {
        priority_queue<long long, vector<long long>, greater<long long>> q;
        for (auto x: v) {
            q.push(x);
        }

        cout << q.top()<<"\n";
    }

    return false;
}

int main()
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        int n;
        cin >> n;

        unordered_set<long long> v;
        for (int j = 0; j < n; ++j) {
            int x;
            cin >> x;
            v.insert(x);
        }

        cout << (is(v) ? "Yes" : "No") << "\n";
    }

    return 0;
}
