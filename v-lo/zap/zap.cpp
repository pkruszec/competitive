#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits.h>

using namespace std;

typedef long long ll;

vector<ll> tree;
ll base = 1;
ll n;

const ll INF = LLONG_MAX;
void init(vector<ll>& a)
{
    n = a.size();
    while (base < n)
        base *= 2;
    tree.resize(2*base, INF);

    for (ll i=0; i<n; i++)
        tree[i+base] = a[i];
    for (ll i=base-1; i>0; i--)
        tree[i] = min(tree[2*i],tree[2*i+1]);
}

ll query(ll a, ll b, ll i = 1, ll ia = 0, ll ib = n-1)
{
    // cout << "QUERY " << a << ", " << b << "  " << i << ", " << ia << ", " << ib << "\n";

    if (b<ia || a>ib) {
        return INF;
    }
    if (a<=ia && ib<=b) {
        //cout << "  returned " << tree[i]<<"\n";
        return tree[i];
    }
    ll s = (ia + ib)/2;
    ll l = query(a,b,2*i,ia,s);
    ll r = query(a,b,2*i+1,s+1,ib);
    return min(l,r);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll n;
    cin >> n;

    vector<ll> A(n);
    for (ll i = 0; i < n; ++i) {
        cin >> A[i];
    }

    init(A);

    ll k;
    cin >> k;

    for (ll i = 0; i < k; ++i) {
        ll a, b;
        cin >> a >> b;
        cout << query(a-1, b-2) << "\n";
    }

    return 0;
}
