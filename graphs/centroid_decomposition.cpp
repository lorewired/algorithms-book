int main(int argc, char** argv) {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;

    vector<vector<int>> g(n), g2(n);

    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v, u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> sz(n), done(n), par(n, -1);

    auto tsize = [&] (this auto&& tsize, int u, int p) -> int {
        sz[u] = 1;
        for (int v : g[u]) {
            if (v == p || done[v]) continue;
            sz[u] += tsize(v, u);
        }
        return sz[u];
    };

    auto centroid = [&] (this auto&& centroid, int u, int p, int tsz) -> int {
        for (int v : g[u]) {
            if (v == p || done[v]) continue;
            if (2 * sz[v] >= tsz) return centroid(v, u, tsz);
        }
        return u;
    };

    auto decompose = [&] (this auto&& decompose, int u) -> int {
        int cen = centroid(u, -1, tsize(u, -1));

        done[cen] = 1;

        for (int v : g[cen]) {
            if (done[v]) continue;
            int vcen = decompose(v);
            par[vcen] = cen;
            g2[cen].push_back(vcen);
        }
        
        return cen;
    };

    decompose(0);

    return 0;
}
