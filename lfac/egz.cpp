#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n, k;
    cin >> n >> k;

    if (k > n/2) {
        cout << "NIE\n";
        return 0;
    }

    int m = (n+1) / 2;

    if (n % 2 == 0) {
        for (int i = 0; i < n/2; ++i) {
            cout << m+1+i << " ";
            cout << 1+i << " ";
        }
        cout << "\n";
    } else {
        for (int i = 0; i <= n/2; ++i) {
            cout << 1+i << " ";
            if (i < n/2)
                cout << m+1+i << " ";
        }
        cout << "\n";
    }
}

