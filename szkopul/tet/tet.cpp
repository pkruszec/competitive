#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    
    stack<int> s;
    stack<int> d;
    
    for (int i = 0; i < n*2; ++i) {
        int x;
        cin >> x;
        s.push(x);
    }
    
    stack<int> i;
    while (!s.empty()) {
        i.push(s.top());
        s.pop();
    }
    
    s = i;
    
    vector<int> moves;
    vector<bool> in_d(n+1, false);
    
    while (!s.empty()) {
        int x = s.top();
        s.pop();
        
        if (!in_d[x]) {
            d.push(x);
            in_d[x] = true;
        } else {
            int j = d.size() - 1;
            int y = d.top();
            d.pop();
            in_d[y] = false;
            
            if (x != y) {
                moves.push_back(j + 1);
                s.push(y);
                s.push(x);
            }
        }
    }
    
    cout << moves.size() << '\n';
    for (auto move: moves) {
        cout << move << '\n';
    }
    
    /*print();
    swap(4);
    print();
    while (collapse());
    print();*/
    
    return 0;
}
