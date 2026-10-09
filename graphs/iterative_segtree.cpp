/* by: lorewired

Iterative Segment-Tree - Sum in Range and Point Update - 0-based and inclusive ranges

Time Complexity:
build - O(n)
mod - O(log(n))
query - O(log(n))

*/

ll tree[MXN];
int n;

void build() {
    for (int i = n - 1; i > 0; i--) {
        tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }
}

void mod(int i, ll x) {
    for (tree[i += n) = x; i > 1; i >>= 1) {
        tree[i >> 1] = tree[i] + tree[i ^ 1];
    }
}

ll query(int l, int r, ll s = 0) {
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1;) {
        if (l & 1) s += tree[l++];
        if (r & 1) s += tree[--r];
    }
    return s;
}
