#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <stdint.h>
#include <limits.h>

using namespace std;

vector<int64_t> fib(93);

int64_t count(int64_t n)
{
    int64_t x = 0;
    int64_t s = 0;

    while (x != n) {
        s++;

        int64_t diff = n - x;
        int64_t ad = abs(diff);
        int64_t md = INT64_MAX;
        int64_t value = 0;

        // TODO: binary search
        for (int i = 1; i < fib.size(); ++i) {
            if (abs(fib[i] - ad) < md) {
                md = abs(fib[i] - ad);
                value = fib[i];
            }
        }

        if (diff < 0) value *= -1;
        x += value;
    }

    return s;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    fib[0] = 0;
    fib[1] = 1;

    for (int64_t i = 2; i < fib.size(); ++i) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    for (int i = 0; i < n; ++i) {
        int64_t k;
        cin >> k;
        cout << count(k) << "\n";
    }

    return 0;
}
