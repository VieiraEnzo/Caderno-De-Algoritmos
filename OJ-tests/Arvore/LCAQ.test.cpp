#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include <bits/stdc++.h>
using namespace std;
#include "../../Algoritmos/Arvore/LCAQ.h"

int main(){

    cin.tie(0), ios_base::sync_with_stdio(false);

    int n, q; cin >> n >> q;

    LCAQ lca(n);

    for(int i = 1; i < n; i++){
        int p; cin >> p;
        lca.add_edge(i, p); 
    }

    lca.build(1);

    while(q--){
        int u, v; cin >> u >> v;
        cout << lca.find_lca(u, v) << "\n";
    }

    return 0;
}
