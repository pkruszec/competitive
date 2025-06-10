#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <limits.h>
#include <intrin.h>
using namespace std;

#define N 1000
#define M 10000

vector<int> xs(N);

int simple(int mi, int ma)
{
    int v = INT_MIN;
    for (int i = mi; i <= ma; ++i) {
        if (xs[i] > v) v = xs[i];
    }
    return v;
}

vector<int> tree(N*4, INT_MIN);

void update(int x, int val, int n)
{
    int v = x+n-1;
    tree[v] = val;
    while (v > 1) {
        v /= 2;
        tree[v] = max(tree[2*v], tree[2*v + 1]);
    }
}

int query(int xl, int xr, int n)
{
    int vl = xl + n - 1;
    int vr = xr + n - 1;
    int w = max(tree[vl], tree[vr]);
    while (vl/2 != vr/2) {
        if (vl%2 == 0) {
            w = max(w, tree[vl+1]);
        }
        if (vr%2 == 1) {
            w = max(w, tree[vr-1]);
        }
        
        vl /= 2;
        vr /= 2;
    }
    return w;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    srand(1);
    
    for (int i = 0; i < xs.size(); ++i) {
        xs[i] = rand() % 1000;
    }
    
    vector<pair<int, int>> rng(M);
    for (int i = 0; i < rng.size(); ++i) {
        int mi = rand() % N;
        int ma = rand() % (N-mi) + mi;
        rng[i] = {mi, ma};
    }
    
    vector<int> ans(M);
    
    __int64 t0 = __rdtsc();
    for (int i = 0; i < ans.size(); ++i) {
        ans[i] = simple(rng[i].first, rng[i].second);
    }
    __int64 t1 = __rdtsc();
    cout << "simple: " << t1 - t0 << "\n";
    
#if TEST
    {
        int r = 1;
        while (r < N) {
            r *= 2;
        }
        for (int i = 0; i < xs.size(); ++i) {
            update(i, xs[i], r);
        }
        
        for (int i = 0; i < ans.size(); ++i) {
            int a = query(rng[i].first, rng[i].second, r);
            if (a != ans[i]) {
                cout << i << ": no match for {" << rng[i].first << ", " << rng[i].second << "}, exp " << ans[i] << ", got " << a << "\n";
                return 0;
            }
        }
        return 0;
    }
#endif
    
    t0 = __rdtsc();
    
    int r = 1;
    while (r < N) {
        r *= 2;
    }
    for (int i = 0; i < xs.size(); ++i) {
        update(i, xs[i], r);
    }
    
    for (int i = 0; i < ans.size(); ++i) {
        ans[i] = query(rng[i].first, rng[i].second, r);
    }
    t1 = __rdtsc();
    cout << "query:  " << t1 - t0 << "\n";
    
    return 0;
}
