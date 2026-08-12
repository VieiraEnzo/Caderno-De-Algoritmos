/**
 * Description: Centroid Decomposition. Decompõe a árvore em centróides recursivamente.
 *     Constrói a árvore de centróides em $O(n \log n)$.
 * Usage: \texttt{build(x, p)} constrói a decomposição.
 *     A árvore de centróides fica armazenada em \texttt{pai}.
 * Time: $O(n \log n)$
 * Status: tested
 */

struct Centroid{
    int n;
    vector<int> used, pai, sub;
    vector<vector<int >> vec;

    Centroid(int n) : n(n), used(n+1), pai(n+1), sub(n+1), vec(n+1) {}

    void add_edge(int v, int u){
        vec[v].push_back(u);
        vec[u].push_back(v);
    }

    int dfs_sz(int x, int p=0){
        sub[x]=1;
        for(int i:vec[x]){
            if(i==p || used[i]) continue;
            sub[x]+=dfs_sz(i, x);
        }
        return sub[x];
    }

    int find_c(int x, int total, int p=0){
        for(int i:vec[x]){
            if(i==p || used[i]) continue;
            if(2*sub[i]>total) return find_c(i, total, x);
        }
        return x;
    }
    
    void build(int x=1, int p=0){
        int c=find_c(x, dfs_sz(x));

        //do something
        
        used[c]=1;
        pai[c]=p;
        for(int i:vec[c]){
            if(!used[i]) build(i, c);
        }
    }
};
