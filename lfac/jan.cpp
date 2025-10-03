#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	long long n;
	cin >> n;

	long long ans = 0;

	long long sm = n*(n+1)/2;
	
	long long l = 0;
	long long k = floor(log2(n));
	
	for (long long j = 0; j <= k; ++j) {
		
		long long p2 = pow(2, j);
		
		l += p2 * min(n - p2 + 1, p2);
	}
	
	ans += sm - l;
	
	cout << ans << "\n";
	
	return 0;
}

/*

0  0   +0
1  0   +0
2  0   +1
3  1   +0
4  1   +0
5  2   +1
6  4   +2
7  7   +3
8  7   +0
9  8   +1
10 10  +2
11 13  +3
12 17  +4
13 22  +5
14 28  +6
15 35  +7
16 35  +0
17 36
18
19
20

*/