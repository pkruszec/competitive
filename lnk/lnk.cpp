#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

int main()
{
    int n1, n2;
    cin >> n1 >> n2;
    vector<int> v1(n1);
    vector<int> v2(n2);

    for (int i = 0; i < n1; ++i) {
        cin >> v1[i];
    }
    for (int i = 0; i < n2; ++i) {
        cin >> v2[i];
    }

    return 0;
}
