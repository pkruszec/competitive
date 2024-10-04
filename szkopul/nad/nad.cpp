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
// * Increment, neighbors done.
// * Do one of these (try in order):
//   * Recurse into 3rd neighbors (if present), previous 2nd neighbor done.
//   * Recurse into 2nd neighbors (if present).
//   * Increment the second time, 2nd neighbors done.
// * Compare total amount of increments with the smallest min.
// 

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

int n;
vector<pair<int, int>> e;

int f(int i, int ig=-1)
{
    int c = 1;
    
    bool idid = false;
    bool vdid = false;
    bool wdid = false;
    for (auto &edge: e) {
        int v;
        if (edge.first == i) {
            v = edge.second;
        } else if (edge.second == i) {
            v = edge.first;
        } else continue;
        if (v == ig) continue;
        
        idid = true;
        // std::cout << v+1 << "\n";
        
        vdid = false;
        for (auto &edge: e) {
            int w;
            if (edge.first == v) {
                w = edge.second;
            } else if (edge.second == v) {
                w = edge.first;
            } else continue;
            if (w == i) continue;
            
            vdid = true;
            // std::cout << w+1 << "\n";
            
            wdid = false;
            for (auto &edge: e) {
                int y;
                if (edge.first == w) {
                    y = edge.second;
                } else if (edge.second == w) {
                    y = edge.first;
                } else continue;
                if (y == v) continue;
                
                // std::cout << y+1 << "\n";
                wdid = true;
                
                int val = f(y, w);
                if (c < 0) return c;
                c += val;
            }
            
            if (!wdid) {
                int val = f(w, v);
                if (c < 0) return c;
                c += val;
            }
        }
    }
    
    // if (!wdid) c += 1;
    if (!vdid) return -2;
    if (!wdid) return -1;
    
    return c;
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
    
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        st >> a >> b;
        e[i] = pair<int, int>(a-1, b-1);
    }
    
    // int c = f(1);
    
    int ci = -1;
    int c = INT_MAX;
    for (int i = 0; i < n; ++i) {
        int x = f(i);
        if (x < c) {
            ci = i;
            c = x;
        }
    }
    
    if (c == -2) {
        std::cout << 1 << "\n";
    } else if (c == -1) {
        std::cout << 2 << "\n";
    } else {
        std::cout << c << "\n";
    }
    
    return 0;
}
