//LCA Path query

struct LCAQ{
    
    const int neutral = 0;
    int n;
    const int sz = 32;
    vector<int> marc, height, val;
    vector<vector<int>> g, bl, tb;

    //Trocar se a raiz nao for 1
    LCAQ(int n) : n(n), g(n+1), bl(sz, vector<int> (n+1, 1)), tb(sz, vector<int> (n+1, 1)), marc(n+1), height(n+1){}

    void add_edge(int a, int b){
        g[a].push_back(b);
        g[b].push_back(a);
    }

    void set_val(int i, int x){
        val[i] = x;
    }

    //Trocar se a raiz nao for 1
    void build(int x = 1){ 
        marc[x] = 1;
        for(int i = 1; i < sz; i++){
            bl[i][x] = bl[i-1][bl[i-1][x]];
            tb[i][x] = tb[i-1][x] + tb[i-1][bl[i-1][x]];
        }

        for(auto viz : g[x]){
            if(marc[viz]) continue;
            bl[0][viz] = x;
            tb[0][viz] = val[x];
            height[viz] = height[x]+1;
            build(viz);
        }
    }

    int find_lca(int a, int b){
        if(height[a] < height[b]) swap(a,b);

        int dif = height[a] - height[b];
        for(int i = 0; i < sz; i++){
            if((1<<i) & dif){
                a = bl[i][a];
            }
        }

        assert(height[a] == height[b]);
        if(a == b) return a;

        for(int i = sz-1; i >=0; i--){
            if(bl[i][a] == bl[i][b]) continue;
            a = bl[i][a];
            b = bl[i][b];
        }
        
        assert(a != b);
        assert(bl[0][a] == bl[0][b]);
        return bl[0][a];
    }

    int dist(int a, int b){
        int l = find_lca(a,b);  
        return height[a] + height[b] - 2*height[l];
    }

    int query_lca(int a, int lca){
        int ans = neutral;
        int dif = height[lca] - height[a];
        for(int i = 0; i < sz; i++){
            if((1<<i) & dif){
                ans = ans + tb[i][a];
                a = bl[i][a];
            }
        }

        assert(a == lca);
        return ans;
    };

    int query(int a, int b){
        int lca = find_lca(a,b);
        return val[a] + val[b] + query(a,lca) + query(b,lca) - val[lca];
    }
};