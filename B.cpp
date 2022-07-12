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
    int n, k; cin >> n >> k;
    vector <ll> ps(n);
    int ans = 0;
    map <ll, int> pos;
    for (int i = 0; i < n; i++) {
        cin >> ps[i];
        if (i) ps[i]+=ps[i-1];
        ll cur = ps[i]%k;
        if (pos.find(cur) == pos.end()) pos[cur] = i;
        else {
            ans = max(ans, i-pos[cur]);
            cout << i << ' ' << pos[cur] << '\n';
        }
    }
    cout << ans;
}

int main()
{
    AboTaha_on_da_code

    // freopen("self.in", "r", stdin);
    /*freopen("output.txt", "w", stdout);*/

    int t = 1; // cin >> t;
    for (int i = 1; i <= t; i++) {
        burn();
        cout << '\n';
    }
    return 0;
}