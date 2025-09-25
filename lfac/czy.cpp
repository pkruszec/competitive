#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    long long n;
    cin >> n;

    if (((n) & (n-1)) == 0) {
        cout << "TAK\n";
    } else {
        cout << "NIE\n";
    }

    return 0;
}

/*

4

while n > 1 {
    if n parzysta
        n /= 2
    else
        n = 3n + 3
}

*/
