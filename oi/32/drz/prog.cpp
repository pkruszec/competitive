#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

int N, q;
string src, dst;

vector<long long> h0, h1;

unordered_map<long long, long long> P;

long long pw(long long a, long long n)
{
    long long x = 1;
    for (long long i = 0; i < n; ++i) {
        x *= a;
    }
    return x;
}

long long p = 5;
long long m = 1'000'000'000'000'000;

long long hsh(long long x, long long y, long long k2)
{
	return (min(x, y)*P[k2]+ max(x, y)) % m;
}

void build(int l=0, int r=src.size()-1, int n=0)
{
	if (r == l) {
        h0[n] = src[l];
        h1[n] = dst[l];
		return;
	}

	int m = (l+r)/2;
	int nl = n*2+1;
	int nr = n*2+2;
	build(l, m, nl);
	build(m+1, r, nr);
	
    int k = r-l+1;

	h0[n] = hsh(h0[nl], h0[nr], k);
	h1[n] = hsh(h1[nl], h1[nr], k);
}

void update(string &s, vector<long long> &h, int b, int l=0, int r=src.size()-1, int n=0)
{
	if (r == l) {
		h[n] = s[l];
		return;
	}
	
	int m = (l+r)/2;
	int nl = n*2+1;
	int nr = n*2+2;
	
    int k = r-l+1;

	if (b <= m) {
		update(s, h, b, l, m, nl);
	} else {
		update(s, h, b, m+1, r, nr);
	}
	
	h[n] = hsh(h[nl], h[nr], k);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> q;
    cin >> src >> dst;
	
	h0.resize(2*src.size());
	h1.resize(2*dst.size());
	
    for (long long x = src.size(); x; x /= 2) {
        P[x] = pw(p, x);
    }

    // for(auto [x, y]: P){
    //     cout << p << "^"<< x << " = " << y << "\n";
    // }
    // return 0;

	build();
    if (h0[0] == h1[0]) {
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
			update(src, h0, b);
        } else {
            dst[b] = v;
			update(dst, h1, b);
        }

        if (h0[0] == h1[0]) {
            cout << "TAK\n";
        } else {
            cout << "NIE\n";
        }
    }

    return 0;
}
