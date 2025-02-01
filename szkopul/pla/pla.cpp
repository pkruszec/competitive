#include <iostream>
#include <limits.h>
#include <numeric>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

int n;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    vector<int> H(n);

    for (int i = 0; i < n; ++i) {
        int w;
        cin >> w >> H[i];
    }

    stack<int> S;
    int p = 0;

    for (int i = 0; i < n; ++i) {
        while (!S.empty() && S.top() > H[i]) {
            S.pop();
        }

        if (S.empty() || S.top() < H[i]) {
            S.push(H[i]);
            p++;
        }
    }

    cout << p << "\n";
    
    return 0;
}
