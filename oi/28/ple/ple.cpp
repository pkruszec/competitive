#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int n;
long long sum;
vector<int> w;

long long check(int k, long long s)
{
    // cout << s <<"\n";
    
    long long c = 0;
    int m = 0;
    for (int i = 0; i < n; ++i) {
        cout << (c) << " + " << w[i] << " -> " << c + w[i] << " " << (c + w[i] <= s ? "<=" : ">") << " " << s << "\n";
        
        if (c + w[i] <= s) {
            c += w[i];
            m++;
        }
        
        if (m >= k) {
            return c;
        }
    }
    
    if (m >= k) {
        return c;
    }
    
    // cout << m << "\n";
    // if(k==5) cout << s << " -> " << c << "\n";
    return -1;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;
    w.resize(n);
    
    sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
        sum += w[i];
    }
    
    cout << me(4) << "\n";
    
#if 0
    for (int k = 1; k <= n; ++k) {
        long long l = 0;
        long long r = sum;
        long long res = LLONG_MAX;
        
        while (l <= r) {
            long long s = (l+r) / 2;
            long long c = check(k, s);
            
            // if (k==5) cout << "s=" << s << " c=" << c << " res=" << res << "\n";
            
            if (c < 0) {
                l = s + 1;
            } else {
                res = c;
                r = s - 1;
            }
        }
        
        cout << res << " ";
        
        if (res >= 0) {
            //goto next;
        }
        
        //next:;
    }
    cout << "\n";
#endif
    
    return 0;
}

/*

*/
