#include <bits/stdc++.h>
#include <cassert>
#include <print>
using namespace std;

typedef long long ll;

int main(int argc, char** argv) {
    cin.tie(0)->sync_with_stdio(0);

    int n, q; cin >> n >> q;

    vector<ll> tree(n << 1);

    for (int i = 0; i < n; i++) {
        cin >> tree[i + n];
    }

    for (int o = n - 1; o > 0; o--) {
        tree[o] = tree[o << 1] + tree[o << 1 | 1];
    }

    auto mod = [&] (int o, ll x) {
        for (tree[o += n] = x; o > 1; o >>= 1) {
            tree[o >> 1] = tree[o] + tree[o ^ 1];
        }
    };

    auto query = [&] (int l, int r, ll s = 0) -> ll {
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) s += tree[l++];
            if (r & 1) s += tree[--r];
        }
        return s;
    };
    
    for (int i = 0; i < q; i++) {
        int t; cin >> t;
        
        if (t == 1) {
            int k; ll x; cin >> k >> x;
            mod(k, x);
        } else {
            int l, r; cin >> l >> r, r--;
            cout << query(l, r) << '\n';
        }
    }
    
    return 0;
}