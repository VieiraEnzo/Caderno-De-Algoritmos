/**
 * Description: Disjoint Set Union (DSU) com path compression e union by rank.
 * Time: $O(\alpha(n))$ amortizado por operação
 * Skip: true
 */

struct DSU
{
    int n;
    vector<int> pai, rank;

    DSU(int n) : n(n), pai(n+1), rank(n+1,1){
        for(int i = 1; i <=n; i++){
            pai[i] = i;
        }
    }

    int find(int a){
        if(pai[a] == a) return a;
        return pai[a] = find(pai[a]);
    }

    void uu(int a, int b){
        a = find(a), b = find(b);
        if(a == b) return;
        if(rank[a] > rank[b]) swap(a,b);
        rank[b] += rank[a];
        pai[a] = b;
    }

};