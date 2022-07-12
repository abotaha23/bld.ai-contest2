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
    int n, q; cin >> n >> q;
    map <string, vector <int>> mp;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        string cur;
        for (auto &j : s) {
            cur.push_back(j);
            mp[cur].push_back(i);
        }
    }
    while(q--) {
        string s; cin >> s;
        cout << mp[s].size() << '\n';
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
//        cout << '\n';
    }
    return 0;
}