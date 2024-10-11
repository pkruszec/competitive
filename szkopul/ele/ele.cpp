//
// Elektrownie i fabryki (ele)
// https://szkopul.edu.pl/problemset/problem/B4XL0I6ifyo5j3dfzVm6mF2r/site/
// 
// not solved (10 pts)

#include <iostream>
#include <vector>
#include <limits.h>
#include <stdint.h>

using namespace std;

int n;
vector<int> xs;

int f(int i)
{
    int s = INT_MAX;
    int val = -xs[i];
    int cs, cv;
    
    // right
    cs = 1;
    cv = 0;
    for (int j = i+1; xs[j] >= 0; ++j, ++cs) {
        cv += xs[j];
        if (cv >= val && cs < s) {
            s = cs;
            break;
        }
    }
    
    
    // left
    cs = 1;
    cv = 0;
    for (int j = i-1; xs[j] >= 0; --j, ++cs) {
        cv += xs[j];
        if (cv >= val && cs < s) {
            s = cs;
            break;
        }
    }
    
    
    if (s == INT_MAX) {
        return -1;
    }
    return s;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;
    xs.resize(n + 2, -99);
    for (int i = 1; i <= n; ++i) {
        cin >> xs[i];
    }
    
    int64_t best = INT_MAX;
    int64_t s = 0;
    
    s = 0;
    for (int i = 1; i <= n; ++i) {
        if (xs[i] < 0) {
            int r = f(i);
            if (r < 0) {
                s = INT_MAX;
                break;
            }
            s += r;
        }
    }
    if (s < best) best = s;
    
    s = 0;
    for (int i = n; i >= 1; --i) {
        if (xs[i] < 0) {
            int r = f(i);
            if (r < 0) {
                s = INT_MAX;
                break;
            }
            s += r;
        }
    }
    if (s < best) best = s;
    
    if (best == INT_MAX)
        cout << "-1\n";
    else
        cout << best << '\n';
    
    /*
    for (auto x: xs) {
        cout << x << ' ';
    }
*/
    
    return 0;
}
