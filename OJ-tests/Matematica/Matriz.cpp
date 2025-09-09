#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_7_D"
#include <bits/stdc++.h>
using namespace std;
#include "../../Algoritmos/Matematica/Matriz.h"
typedef long long ll;

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n,m,l; cin >> n >> m >> l;
    M a(n,m), b(m,l);

    for(int i = 0; i < n; i++){
        for(int j =0; j < m; j++){
            cin >> a[i][j];
        }
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < l; j++){
            cin >> b[i][j];
        }
    }
    
    M c = a*b;

    for(int i = 0; i < c.n; i++){
        for(int j = 0; j < c.m; j++){
            cout << c.mat[i][j] << " ";
        }cout << "\n";
    }

    return 0;
}
