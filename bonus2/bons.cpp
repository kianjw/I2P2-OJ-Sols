#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define sz(s) (int)s.size()
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int mod = 1e9 + 7;
const int N = 300300;
int n, a[N], col[N], cnt_col[N];
bool was[N], init_good;
ll ans;
bool used[N];
 
void f(int v) {
    if (col[v] != -1)
        return;
    if (was[v]) {
        col[v] = v;
        return;
    }
    if (used[v]) {
        col[v] = v;
        return;
    }
    used[v] = 1;
    int u = v + a[v];
    if (u < 1 || u > n)
        col[v] = 0;
    else {
        f(u);
        col[v] = col[u];
    }
}
 
void solve() {
    ans = 0;
    init_good = false;
 
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
 
    for (int i = 1; i <= n; i++)
        was[i] = 0;
    {
        int v = 1;
        while (true) {
            was[v] = 1;
            v += a[v];
            if (v < 1 || v > n) {
                init_good = 1;
                break;
            }
            if (was[v])
                break;
        }
    }
    for (int i = 1; i <= n; i++)
        col[i] = -1, used[i] = 0;
    for (int i = 1; i <= n; i++)
        f(i);
 
    for (int i = 0; i <= n; i++)
        cnt_col[i] = 0;
    for (int i = 1; i <= n; i++)
        cnt_col[col[i]]++;
 
    {
        ll s = cnt_col[0];
        if (init_good) {
            for (int i = 1; i <= n; i++)
                if (was[i])
                    s += cnt_col[i];
        }
        for (int i = 1; i <= n; i++)
            was[i] = 0;
        int v = 1;
        while (true) {
            if (init_good)
                s -= cnt_col[v];
            ans += s;
            ans += n + 1;
            was[v] = 1;
            v += a[v];
            if (v < 1 || v > n || was[v])
                break;
        }
        for (int i = 1; i <= n; i++)
            if (!was[i] && init_good)
                ans += n + n + 1;
    }
 
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);  
    int tt;
    cin >> tt;
    while (tt--) solve();
    return 0;
}