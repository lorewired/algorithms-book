#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef long long ll;

// 1-BASED !!

int main(int argc, char** argv) {
    cin.tie(0)->sync_with_stdio(0);
    
    int n; cin >> n;
    vector<int> v(n);

    int mn = 2e9, mx = 0;

    for (int i = 0; i < n; i++) {
        cin >> v[i];
        mn = min(mn, v[i]);
        mx = max(mx, v[i]);
    }

    struct wavelet {
        using vit = vector<int>::iterator;
        
        int lo, hi;
        
        wavelet* L = nullptr;
        wavelet* R = nullptr;

        vector<int> pref;

        wavelet(vit from, vit to, int mn, int mx) {
            lo = mn, hi = mx;
            if (lo == hi || from >= to) return;
            int mid = lo + (hi - lo) / 2;
            auto f = [&mid] (int x) -> bool {
                return x <= mid;
            };
            pref.reserve(to - from + 1);
            pref.push_back(0);
            for (auto it = from; it != to; it++) {
                pref.push_back(pref.back() + f(*it));
            }
            auto pivot = stable_partition(from, to, f);
            L = new wavelet(from, pivot, lo, mid);
            R = new wavelet(pivot, to, mid + 1, hi);
        }

        int lte(int l, int r, int k) {
            if (l > r || lo > k) return 0;
            if (hi <= k) return r - l + 1;
            int lb = pref[l - 1], rb = pref[r];
            return L->lte(lb + 1, rb, k) + R->lte(l - lb, r - rb, k);
        }

        int kth(int l, int r, int k){
            if (l > r) return 0;
            if (lo == hi) return lo;
            int in_lf = pref[r] - pref[l - 1];
            int lb = pref[l - 1];
            int rb = pref[r];
            if (k <= in_lf) return L->kth(lb + 1, rb , k);
            return R->kth(l - lb, r - rb, k - in_lf);
        }

        int count(int l, int r, int k) {
            if (l > r or k < lo or k > hi) return 0;
            if (lo == hi) return r - l + 1;
            int lb = pref[l - 1], rb = pref[r], mid = lo + (hi - lo) / 2;
            if (k <= mid) return L->count(lb + 1, rb, k);
            return R->count(l - lb, r - rb, k);
        }

        ~wavelet() {
            delete L;
            delete R;
        }
    };

    wavelet tree(begin(v), end(v), mn, mx);

    return 0;
}
