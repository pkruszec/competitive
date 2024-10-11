//
// Paweł Kruszec <pakruszec@gmail.com>
// Nadajniki (nad)
// https://szkopul.edu.pl/problemset/problem/sKmyIHBMNi9EV3WO6GQ4xoFt/site/
// https://oi.edu.pl/static/attachment/20171006/oi23.pdf
//
// not solved
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

int n;
vector<pair<int, int>> e;
vector<vector<vector<vector<int>>>> ts;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
#if REMEDY
    ifstream st("input01.txt");
#else
    auto &st = cin;
#endif
    
    st >> n;
    e.resize(n - 1);
    ts.resize(n, {3, {3, {3, {}}}});
    
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        st >> a >> b;
        e[i] = pair<int, int>(a-1, b-1);
    }
    
    
    
    // std::cout << c << "\n";
    
    return 0;
}
