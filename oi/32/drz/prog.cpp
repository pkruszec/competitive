#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <unordered_set>
#include <algorithm>
#include <cassert>

using namespace std;

int n, q;
string src, dst;

vector<long long> h0, h1;

/*long long hash0(string_view s)
{
	if (s.size() == 2) {
		long long h0 = s[0];
		long long h1 = s[1];
		long long result = h0*h1 - h0 - h1;
		return result;
	}
	
	int m = s.size()/2;
	long long h0 = hash0(s.substr(0, m));
	long long h1 = hash0(s.substr(m));
	
	long long result = h0 * h1 - h0 - h1;
	return result;
}*/

long long hsh(long long x, long long y)
{
	return (x+y)*(x+y+1)/ 2 *(x+y-2);
	//return x*y - x - y;
}

void build(int l=0, int r=src.size()-1, int n=0)
{
	if (r == l+1) {
		h0[n] = hsh(src[l], src[r]);
		h1[n] = hsh(dst[l], dst[r]);
		return;
	}
	
	int m = (l+r)/2;
	int nl = n*2+1;
	int nr = n*2+2;
	build(l, m, nl);
	build(m+1, r, nr);
	
	h0[n] = hsh(h0[nl], h0[nr]);
	h1[n] = hsh(h1[nl], h1[nr]);
}

void update(string &s, vector<long long> &h, int b, int l=0, int r=src.size()-1, int n=0)
{
	if (r == l+1) {
		h[n] = hsh(s[l], s[r]);
		return;
	}
	
	int m = (l+r)/2;
	int nl = n*2+1;
	int nr = n*2+2;
	
	if (b <= m) {
		update(s, h, b, l, m, nl);
	} else {
		update(s, h, b, m+1, r, nr);
	}
	
	h[n] = hsh(h[nl], h[nr]);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    cin >> src >> dst;
	
	h0.resize(2*src.size());
	h1.resize(2*dst.size());
	
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
