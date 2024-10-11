#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

void fak(unordered_map<int, int> &m, int n)
{
    int x = n;
    for (int i = 2; (i < n);) {
        if (x % i == 0) {
            x /= i;
            m[i]++;
        } else {
            i++;
        }
        if (x == 1) break;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int z;
    cin >> z;
    
    for (int i = 0; i < z; ++i) {
        int n;
        cin >> n;
        cout << n << " = ";
        
        unordered_map<int, int> m;
        fak(m, n);
        
        vector<pair<int, int>> ps;
        for (auto &p: m) {
            ps.push_back(p);
        }
        sort(ps.begin(), ps.end(), [](auto &a, auto &b){
                 return a.first < b.first;
             });
        
        for (int j = 0; j < ps.size(); ++j) {
            auto p = ps[j];
            
            if (j > 0) cout << '*';
            
            if (p.second > 1)
                cout << p.first << '^' << p.second;
            else
                cout << p.first;
        }
        
        cout << '\n';
    }
    
    return 0;
}
