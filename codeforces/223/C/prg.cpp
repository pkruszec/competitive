#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define REP(i,n) for (int i = 0; i < (n); ++i)

#if 0
template <typename ... T>
void put(T &&...args) {
    ([&]{
        cerr << args << " ";
    }(), ...);
    cerr << '\n';
}
#else
# define put(...)
#endif

string b;
int n;

int Q(int l, int r) {
    int k = 0;
    int s = 0;
    int d = 0;

    put("       ", l,r);

    for (int i = l; i <= r; ++i) {
        put("            ", i, b[i]);

        if (b[i] == '(') {
            k++;
        } else if (b[i] == ')') {
            k--;
        }

        if (k < 0) {
            k = 0;
            d = 0;
        } else {
            d++;
        }

        if (k == 0) {
            s += d;
            d = 0;
            put("            SET! d=", d);
        }
    }

    //put("k=",k,d);
    s += d-k;

    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> b >> n;

    REP(i, n) {
        int l,r;
        cin >> l >> r;
        cout << Q(l-1,r-1) << "\n";
        put("-----------------------------");
    }
}
