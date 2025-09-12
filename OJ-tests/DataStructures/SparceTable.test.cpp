#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include <bits/stdc++.h>
using namespace std;
#include "../../Algoritmos/DataStructures/SparceTable.h"

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    SparseTable st(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        if(q%2) cout << st.query(l,r-1) << '\n';
        else cout << st.querylog(l,r-1) << "\n";
    }
    return 0;
}
