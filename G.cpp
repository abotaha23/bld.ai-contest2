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

vector <int> par, dep;
vector <pair<int, int>> dp[20];
vector <vector <pair<int, int>>> adj;

int fnd(int ch)
{
    if (par[ch] == ch) return ch;
    return par[ch] = fnd(par[ch]);
}

bool uni(int f, int s)
{
    f = fnd(f), s = fnd(s);
    if (f == s) return false;
    par[f] = s;
    return true;
}

int get_lca(int f, int s)
{
    if (dep[f] < dep[s]) swap(f, s);
    int k = dep[f]-dep[s], res = 2e9;
    for (int i = 19; ~i; i--) {
        if (k&(1<<i)) {
            k-=(1<<i);
            res = min(res, dp[i][f].Y);
            f = dp[i][f].X;
        }
    }
    if (f == s) return res;
    for (int i = 19; ~i; i--) {
        if (dp[i][f].X != dp[i][s].X) {
            res = min({res, dp[i][f].Y, dp[i][s].Y});
            f = dp[i][f].X, s = dp[i][s].X;
        }
    }
    res = min({res, dp[0][f].Y, dp[0][s].Y});
    return res;
}

void dfs(int cur = 0, pair<int, int> p = {0, 0}, int d = 0)
{
    dp[0][cur] = p;
    dep[cur] = d;
    for (auto &i : adj[cur]) {
        if (i.X == p.X) continue;
        dfs(i.X, {cur, i.Y}, d+1);
    }
}

void burn()
{
    int n, m; cin >> n >> m;
    vector <array <int, 3>> edges(m);
    par.resize(n);
    iota(par.begin(), par.end(), 0);
    for (auto &i : dp) i.resize(n);
    dep.resize(n);
    for (auto &i : edges) {
        cin >> i[1] >> i[2] >> i[0];
        i[1]--, i[2]--;
    }
    sort(edges.rbegin(), edges.rend());
    adj.resize(n);
    for (auto &i : edges) {
        if (uni(i[1], i[2])) {
            adj[i[1]].push_back({i[2], i[0]});
            adj[i[2]].push_back({i[1], i[0]});
        }
    }
    dfs();
    for (int i = 1; i < 20; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j].X = dp[i-1][dp[i-1][j].X].X;
            dp[i][j].Y = min(dp[i-1][j].Y, dp[i-1][dp[i-1][j].X].Y);
        }
    }
    int q; cin >> q;
    while(q--) {
        int a, b; cin >> a >> b;
        a--, b--;
        cout << get_lca(a, b) << '\n';
    }
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