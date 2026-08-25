/**
 * Description: LCA com binary lifting e query de soma em caminhos.
 *     Armazena valores nos vértices (set_val antes do build) e responde
 *     a soma dos valores no caminho entre dois nós.
 * Usage: \texttt{set\_val(i, x)} define o valor do vértice \texttt{i}.
 *     \texttt{build(root)} constrói a partir da raiz (padrão: 0).
 *     \texttt{query(a, b)} retorna a soma dos valores no caminho a-b.
 * Time: $O(n \log n)$ de build, $O(\log n)$ por query
 * Status: https://cses.fi/problemset/task/1135 (fraco)
 */

struct LCAQ{

    int n, lg = 29, neutral = 0;
    vector<int> height, val;
    vector<vector<int>> g, bl, tb;

    LCAQ(int n) : n(n), g(n+1), bl(lg, vector<int> (n+1)), tb(lg, vector<int> (n+1, 1)), height(n+1), val(n+1){}

    void add_edge(int a, int b){
        g[a].push_back(b);
        g[b].push_back(a);
    }

    void set_val(int i, int w){
        val[i] = w;
    }

    void build(int x = 0){
        for(int i = 1; i < lg; i++){
            bl[i][x] = bl[i-1][bl[i-1][x]];
            tb[i][x] = tb[i-1][x] + tb[i-1][bl[i-1][x]];
        }

        for(auto viz : g[x]){
            if(bl[0][x] == viz) continue;
            bl[0][viz] = x;
            tb[0][viz] = val[x];
            height[viz] = height[x]+1;
            build(viz);
        }
    }

    pair<int,int> lift(int x, int k){
        int ans = neutral;
        for(int i = 0; i < lg; i++){
            if((1<<i) & k){
                ans = ans + tb[i][x];
                x = bl[i][x];
            }
        }
        return {x, ans};
    }

    int find_lca(int a, int b){
        if(height[a] < height[b]) swap(a,b);

        a = lift(a, height[a] - height[b]).first;
        if(a == b) return a;

        for(int i = lg-1; i >= 0; i--){
            if(bl[i][a] == bl[i][b]) continue;
            a = bl[i][a];
            b = bl[i][b];
        }

        return bl[0][a];
    }

    ll query(int a, int b){
        int l = find_lca(a,b);
        return val[a] + val[b] + lift(a, height[a] - height[l]).second + lift(b, height[b] - height[l]).second - val[l];
    }

};