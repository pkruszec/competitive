#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    vector<int> w(n);
    
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
        sum += w[i];
    }
    
    for (int k = 1; k <= n; ++k) {
        for (long long s = 0; s <= sum; ++s) {
            long long c = 0;
            int m = 0;
            for (int i = 0; i < n; ++i) {
                if (c + w[i] <= s) {
                    c += w[i];
                    m++;
                }
                
                if (m >= k) {
                    cout << c << " ";
                    goto next;
                }
            }
            
            if (m >= k) {
                cout << c << " ";
                goto next;
            }
        }
        
        next:;
    }
    cout << "\n";
    
    return 0;
}
