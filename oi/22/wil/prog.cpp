#include <stdint.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int64_t n, p, d;
vector<int64_t> w;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> p >> d;
    w.resize(n + 1);

    for (int64_t i = 1; i <= n; ++i) {
        cin >> w[i];
        w[i] += w[i-1];
    }

    priority_queue<pair<int64_t, int64_t>> q;

    int64_t ans = d;
    int64_t j = d;
    q.push({w[d], 1});
    
    for (int64_t i = 1; i <= n-d+1; ++i) {
        while (!q.empty() && q.top().second < i) q.pop();
        while (j < n && (w[j+1] - w[i-1] - max(q.top().first, w[j+1] - w[j+1-d]) <= p)) {
            q.push({w[j+1] - w[j+1-d], j+2-d});
            j++;
        }

        ans = max(ans, j-i + 1);
    }

    cout << ans << "\n";

    return 0;
}
