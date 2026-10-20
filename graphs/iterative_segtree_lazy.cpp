int main(int argc, char** argv) {
    cin.tie(0)->sync_with_stdio(0);

    int n, q; cin >> n >> q;

    int LOG = 1;
    if (n > 1) {
        LOG = 32 - __builtin_clz(n - 1);
        n = 1 << LOG;
    }

    vector<ll> tree(n << 1), d(n);

    auto apply = [&] (int p, ll v, int len) {
        tree[p] += v * len;
        if (p < n) {
            d[p] += v;
        }
    };

    auto build = [&] (int p) {
        int len = 2;
        while (p > 1) {
            p >>= 1;
            tree[p] = tree[p << 1] + tree[p << 1 | 1] + d[p] * len;
            len <<= 1;
        }
    };

    auto mod = [&] (int l, int r, ll v) {
        l += n, r += n;
        int _l = l, _r = r;
        for (int len = 1; l < r; l >>= 1, r >>= 1, len <<= 1) {
            if (l & 1) apply(l++, v, len);
            if (r & 1) apply(--r, v, len);
        }
        build(_l), build(_r - 1);
    };

    auto spr = [&] (int p) {
        for (int i = LOG; i > 0; i--) {
            int k = p >> i;
            if (d[k]) {
                int len = 1 << (i - 1);
                apply(k << 1, d[k], len);
                apply(k << 1 | 1, d[k], len);
                d[k] = 0;
            }
        }
    };

    auto query = [&] (int l, int r, ll s = 0) -> ll {
        l += n, r += n;
        spr(l), spr(r - 1);
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) s += tree[l++];
            if (r & 1) s += tree[--r];
        }
        return s;
    };

    for (int i = 0; i < q; i++) {
        int t; cin >> t;
        
        if (t == 1) {
            int l, r; ll v; cin >> l >> r >> v;
            mod(l, r, v);
        } else {
            int l, r; cin >> l >> r;
            cout << query(l, r) << '\n';
        }
    }
    
    return 0;
}