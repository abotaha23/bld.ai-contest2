#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#define AboTaha_on_da_code ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define X first
#define Y second

const int dx[8]={0, 0, 1, -1, 1, -1, -1, 1}, dy[8]={1, -1, 0, 0, 1, -1, 1, -1};
const ll M = 1e9+7, M2 = 998244353;
const double EPS = 1e-8;

void burn()
{
    ll h, a, b; cin >> h >> a >> b;
    ll lev1 = 0, lev2 = 0;
    while(a%2==0) lev1++, a/=2;
    while(b%2==0) lev2++, b/=2;
    a++, a/=2, b++, b/=2;
    lev1 = h-lev1, lev2 = h-lev2;
    while(lev1 > lev2) lev1--, a++, a/=2;
    while(lev1 < lev2) lev2--, b++, b/=2;
    while(a != b) {
        a++, a/=2;
        b++, b/=2;
        lev1--, lev2--;
    }
    cout << (ll)pow(2, h-lev1)*(2*a-1);
}

int main()
{
    AboTaha_on_da_code

    // freopen("self.in", "r", stdin);
    /*freopen("output.txt", "w", stdout);*/

    int t = 1; cin >> t;
    for (int i = 1; i <= t; i++) {
        burn();
        cout << '\n';
    }
    return 0;
}