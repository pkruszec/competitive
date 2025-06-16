#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <cassert>

using namespace std;

int n, q;
string src, dst;

bool eq(string_view a, string_view b)
{
    assert(a.size() == b.size());
    if (a.size() == 1) {
        return a == b;
    }

    int m = a.size()/2;

    auto al = a.substr(0, m);
    auto ah = a.substr(m);

    auto bl = b.substr(0, m);
    auto bh = b.substr(m);

    bool result = ((eq(al, bl) && eq(ah, bh)) || (eq(al, bh) && eq(ah, bl)));// && (a == b || a == bh+bl);
    //cout << a << " == " << b << " -> " << result << "\n";

    return result;
}

/*
vector<bool> t;
void build(int l, int r, int n)
{
    if (r <= l) {
        return;
    }
    int nl = n*2+1;
    int nr = n*2+2;
    int m = (l+r)/2;
    build(l, m, nl);
    build(m+1, r, nr);

    string ss = src.substr(l, r-l+1);
    string ds = dst.substr(l, r-l+1);
    // string dd = dst.substr(m+1, r-(m+1)+1) + dst.substr(l, m-l+1);
    
    t[n] = (t[nl] && t[nr]) || (ss == ds) || (ss == dd);
    cout << ss << " | " << ds << " -> " << t[n] << "\n";
}

void update(int l, int r, int n, int b)
{
}
*/

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    cin >> src >> dst;

    //t.resize(2*src.size(), false);

    // build(0, src.size() - 1, 0);
    if (eq(string_view(src), string_view(dst))) {
        cout << "TAK\n";
    } else {
        cout << "NIE\n";
    }

    for (int i = 0; i < q; ++i) {
        int a, b;
        char v;
        cin >> a >> b >> v;

        b -= 1;

        if (a == 1) {
            src[b] = v;
        } else {
            dst[b] = v;
        }

        // update(0, src.size() - 1, 0, b);
        
        //cout << src << "==" << dst << "? ";

        if (eq(string_view(src), string_view(dst))) {
            cout << "TAK\n";
        } else {
            cout << "NIE\n";
        }
    }

    return 0;
}
