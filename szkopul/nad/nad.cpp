//
// Paweł Kruszec <pakruszec@gmail.com>
// Nadajniki (nad)
// https://szkopul.edu.pl/problemset/problem/sKmyIHBMNi9EV3WO6GQ4xoFt/site/
//
// not solved
//
////////////////////////////////
// ALGORITHM
//
// Try for each vertex, keep the smallest value:
// * Increment, set neighbors done.
// * Do one of these (try in order):
//   * Recurse into 3rd neighbors (if present), set previous 2nd neighbor done.
//   * Recurse into 2nd neighbors (if present).
//   * Increment the second time, set 2nd neighbors done.
// * Compare total amount of increments with the smallest min.
// 

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Rank {
    int first;
    int second;
    int third;
};

int n;
vector<pair<int, int>> e;
vector<bool> done;
vector<int> nad;
vector<Rank> s;

int rel(int v, int &third, bool d = false)
{
    int c = 0;
    int it = -1;
    for (auto &x: e) {
        it++;
        if (done[it]) continue;
        int u;
        if (x.first == v) {
            u = x.second;
        } else if (x.second == v) {
            u = x.first;
        } else {
            continue;
        }
        
        c += 1;
        
        int t;
        if (!d)
            third += rel(u, t, true) - 1;
    }
    return c;
}

bool is_done(int ee)
{
    auto &y = e[ee];
    if ((nad[y.first]) || nad[y.second]) {
        return true;
    }
    
    int c = 0;
    
    for (auto &x: e) {
        int u;
        if (x.first == y.first) {
            u = x.second;
        } else if (x.second == y.first) {
            u = x.first;
        } else {
            continue;
        }
        if (u == ee) continue;
        c += nad[u];
    }
    
    for (auto &x: e) {
        int u;
        if (x.first == y.second) {
            u = x.second;
        } else if (x.second == y.second) {
            u = x.first;
        } else {
            continue;
        }
        if (u == ee) continue;
        c += nad[u];
    }
    
    return c >= 2;
}

bool all_done()
{
    for (int i = 0; i < done.size(); ++i) {
        if (!done[i]) return false;
    }
    return true;
}

int best()
{
    int it = -1;
    int val = 0;
    
    for (int i = 0; i < n; ++i) {
        s[i].first = i;
        s[i].second = rel(i, s[i].third);
        
        int vc = s[i].second +  s[i].third;
        // int vc = s[i].third;
        
        if (vc > val) {
            it = i;
            val = vc;
        }
    }
    
    std::cout << "BEST " << it+1 << " -> " << val << "\n";
    return it;
}

int put()
{
    int sum = 0;
    while (true) {
        int i = best();
        if (i < 0) break;
        
        int k = s[i].first;
        int r = s[i].second;
        int t = s[i].third;
        
        if (all_done()) break;
        
        // int v = t > 0 ? 2 : 1;
        int v = 1;
        nad[k] += v;
        sum += v;
        
        for (int j = 0; j < e.size(); ++j) {
            if (is_done(j)) done[j] = true;
        }
        
        std::cout << k+1 << "\n";
        for (int x = 0; x < (n-1); ++x) {
            std::cout << e[x].first+1 << "->" << e[x].second+1 <<  "("<<done[x]<<")" << " ";
        }
        std::cout << "\n";
    }
    return sum;
}

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
    done.resize(n - 1);
    nad.resize(n);
    s.resize(n);
    
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        st >> a >> b;
        e[i] = pair<int, int>(a-1, b-1);
    }
    
    
    /*
    std::sort(s.begin(), s.end(), [](auto &a, auto &b) {
                  return b.second < a.second;
              });
    */
    
    /*
    for (int i = 0; i < n; ++i) {
        std::cout << s[i].first << ", " << s[i].second << "\n";
    }
*/
    
    int c = put();
    
    std::cout << c << "\n";
    
    return 0;
}
