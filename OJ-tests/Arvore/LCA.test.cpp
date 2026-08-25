#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include <bits/stdc++.h>
using namespace std;
#include "../../Algoritmos/Arvore/LCA.h"

int main(){ 

    cin.tie(0), ios_base::sync_with_stdio(false);

    int n,q ; cin >> n >> q;

    LCA lca(n);

    for(int i = 1; i < n; i++){
        int p; cin >> p;
        lca.add_edge(p, i);
    }

    lca.build();

    while(q--){
        int u, v;
        cin >> u >> v;
        cout << lca.find_lca(u, v) << "\n";
    }

    return 0;

}