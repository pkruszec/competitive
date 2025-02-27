#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <limits.h>

using namespace std;

// int diff(string &s, int i, int j)
// {
//     unordered_map<char, int> c;
//     for (int k = i; k < j; ++k) {
//         c[s[k]]++;
//     }

//     int mi = INT_MAX;
//     int ma = 0;
//     for (auto [x, d]: c) {
//         if (d < mi && d >= 1)
//             mi = d;
//         if (d > ma)
//             ma = d;
//     }

//     return ma - mi;
// }

struct R {
    int most;
    int least;
    char best;
    char worst;
};

R f(string &s, int i, int j)
{
    int n = s.size();
    if ((j - i) < 2) {
        char c = s[i];
        return {
            1, 1, c, c
        };
    }

    R l = f(s, i, i + (j-i)/2);
    R r = f(s, i + (j-i)/2, j);

    unordered_map<char, int> m;
    m[l.best] += l.most;
    m[l.worst] += l.least;
    m[r.best] += r.most;
    m[r.worst] += r.least;

    int most = 0;
    int least = INT_MAX;
    char best = 0;
    char worst = 0;

    for (auto [c, d]: m) {
        if (d >= 1 && (d < least || (d == least && c != worst))) {
            least = d;
            worst = c;
        }
        if (d > most) {
            most = d;
            best = c;
        }
    }

    // int most = max(l.most, r.most);
    // int least = min(l.least, r.least);
    // char best = 0;
    // char worst = 0;

    cout << i << ", " << j << "\n";
    cout << "   part: " << i << "/" << (i + (j-i)/2)  << "/" << j << "\n";
    cout << "   left: " << l.best << ", " << l.worst << "\n";
    cout << "   rigt: " << r.best << ", " << r.worst << "\n";
    cout << "   most: " << most << "\n";
    cout << "   lest: " << least << "\n";
    cout << "   best: " << best << "\n";
    cout << "   wrst: " << worst << "\n";

    return {most, least, best, worst};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;

    // int v = 0;
    // for (int i = 0; i < n; ++i) {
    //     for (int j = i+1; j <= n; ++j) {
    //         int d = diff(s, i, j);
    //         if (d > v) {
    //             v = d;
    //         }
    //     }
    // }
    // cout << v << "\n";

    R r = f(s, 0, n);

    cout << r.most - r.least << "\n";

    return 0;
}


/*

aabbaaabab

babccc
---+++
2,1 3,3
++++++
2

aa(0) + bb(0) = 0
bbaaa(1) + bab(1) = 0

a(3) b(2)
b(2) a(1)

*/