//Virtual Tree
// Créditos: Caderno do Tiago que pegou do Caderno da UFMG
// O(NlogN), sendo N o tamanho do conjunto de vértices passados
/*
Dado o conjunto de vértices do vector v, uma árvore minimal com esse conjunto
é construida, a virtual tree possui no máximo 2*n-1 vértices

virt[i] guarda os vizinhos do vértice i, 
com um pair que guarda o vértice e a distância até ele
*/

vector<pair<int, int> > virt[mxn];

int build(vector<int> v){
    auto cmp = [&](int a, int b) {return tempo[a]<tempo[b];};
    sort(v.begin(), v.end(), cmp);
    for(int i=(int)v.size()-1; i>0; i--) v.push_back(lca(v[i], v[i-1]));
    sort(v.begin(), v.end(), cmp);
    v.erase(unique(v.begin(), v.end()), v.end());
    for(int i=0; i<v.size(); i++) virt[v[i]].clear();
    for(int i=1; i<v.size(); i++) virt[lca(v[i], v[i-1])].clear();
    for(int i=1; i<v.size(); i++){
        int pai = lca(v[i], v[i-1]);
        int d = dist(pai, v[i]);
        virt[pai].emplace_back(v[i], d);
    }
    return v[0];
}