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

vector <vector <int>> adj;
vector <int> low_link, ids, assigned_val
            , comp_assigned_val, comp_root
            , comp, instack;
stack <int> st;
int id, comp_id, n, m;

void tarjan(int cur)
{
    ids[cur] = low_link[cur] = id++;
    instack[cur] = true;
    st.push(cur);
    for (auto &ch : adj[cur]) {
        if (~ids[ch]) {
            if (instack[ch])
                low_link[cur] = min(low_link[cur], ids[ch]);
        }
        else {
            tarjan(ch);
            low_link[cur] = min(low_link[cur], low_link[ch]);
        }
    }
    if (low_link[cur] == ids[cur]) {
        int x = -1;
        while(x != cur) {
            x = st.top(), st.pop(), instack[x] = false;
            comp[x] = comp_id;
        }
        comp_root[comp_id++] = cur;
    }
}

bool assign_vals()
{
    for (int i = 0; i < n; i++) {
        if (!~ids[i]) tarjan(i);
    }

    for (int i = 0; i < n; i+=2) {
        if (comp[i] == comp[i+1]) return false;
    }

    for (int i = 0; i < comp_id; i++) {
        if (!~comp_assigned_val[i]) {
            comp_assigned_val[i] = 1;
            comp_assigned_val[comp[comp_root[i]^1]] = 0;
        }
    }
    for (int i = 0; i < n; i++)
        assigned_val[i] = comp_assigned_val[comp[i]];
    return true;
}

void burn()
{
    cin >> m >> n; n*=2;

    low_link.assign(n, -1), ids.assign(n, -1);
    adj.assign(n, {});
    comp_assigned_val.assign(n, -1);
    comp.resize(n), comp_root.resize(n);
    assigned_val.resize(n);
    instack.assign(n, false);
    while(!st.empty()) st.pop();
    id = comp_id = 0;

    while(m--) {
        int a, b; cin >> a >> b;
        if (a < 0) {
            a++;
            a*=-2;
            if (b < 0) {
                b++;
                b*=-2;
                adj[a].push_back(b+1);
                adj[b].push_back(a+1);
            }
            else {
                b--;
                b*=2;
                adj[a].push_back(b);
                adj[b+1].push_back(a+1);
            }
        }
        else {
            a--;
            a*=2;
            if (b < 0) {
                b++;
                b*=-2;
                adj[a+1].push_back(b+1);
                adj[b].push_back(a);
            }
            else {
                b--;
                b*=2;
                adj[a+1].push_back(b);
                adj[b+1].push_back(a);
            }
        }
    }
    if (!assign_vals()) cout << -1;
    else {
        for (int i = 0; i < n; i+=2)
            cout << assigned_val[i] << ' ';
    }
}

int main()
{
    AboTaha_on_da_code

    // freopen("self.in", "r", stdin);
    /*freopen("output.txt", "w", stdout);*/

    int T = 1; // cin >> T;
    for (int i = 1; i <= T; i++) {
        burn();
        cout << '\n';
    }
    return 0;
}
