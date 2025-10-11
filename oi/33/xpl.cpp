#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long long x, y;
    cin >> x >> y;

    cout << (x+y) << "\n";
    
    return 0;
}

