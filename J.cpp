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

ll dp[20][(1<<20)+1];
int n;
vector <vector <int>> mat;

ll go(int x = 0, int taken = 0)
{
    if (x == n) return 1;
    ll &ret = dp[x][taken];
    if (~ret) return ret;
    ret = 0;
    for (int i = 0; i < n; i++) {
        if (mat[x][i] && !((1<<i)&taken))
            ret+=go(x+1, taken+(1<<i));
    }
    return ret;
}

void burn()
{
    cin >> n;
    memset(dp, -1, sizeof dp);
    mat.resize(n, vector <int>(n));
    for (auto &i : mat) for (auto &j : i) cin >> j;
    cout << go()%M;
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