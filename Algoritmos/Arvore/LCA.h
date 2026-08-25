/**
 * Description: LCA com binary lifting. Encontra o menor ancestral comum,
 *     distância entre vértices e verifica se um vértice está no caminho entre dois outros.
 * Usage: \texttt{build(x)} constrói a estrutura a partir da raiz (padrão: 0).
 *     Se a raiz não for 0, trocar no build() e o valor inicia de bl.
 * Time: $O(n \log n)$ de build, $O(\log n)$ por query
 * Status: tested
 */

struct LCA{
    
    int n, lg = 30;
    vector<int> height;
    vector<vector<int>> g, bl;

    LCA(int n) : n(n), g(n+1), bl(lg, vector<int> (n+1)), height(n+1){}

    void add_edge(int a, int b){
        g[a].push_back(b);
        g[b].push_back(a);
    }

    void build(int x = 0){ 
        for(int i = 1; i < lg; i++){
            bl[i][x] = bl[i-1][bl[i-1][x]];
        }

        for(auto viz : g[x]){
            if(bl[0][x] == viz) continue;
            bl[0][viz] = x;
            height[viz] = height[x]+1;
            build(viz);
        }
    }

    int lift(int x, int k){
        for(int i = 0; i < lg; i++){
            if((1<<i) & k) {
                x = bl[i][x];
            }
        }
        return x;
    }

    int find_lca(int a, int b){
        if(height[a] < height[b]) swap(a,b);

        a = lift(a, height[a] - height[b]);
        if(a == b) return a;

        for(int i = lg-1; i >=0; i--){
            if(bl[i][a] == bl[i][b]) continue;
            a = bl[i][a];
            b = bl[i][b];
        }
        
        return bl[0][a];
    }

    int dist(int a, int b){
        int l = find_lca(a,b);  
        return height[a] + height[b] - 2*height[l];
    }

    // Returns true if x is on the simple path between a and b
    bool on_path(int x, int a, int b){
        return dist(a, b) == dist(a, x) + dist(x, b);
    }


};
