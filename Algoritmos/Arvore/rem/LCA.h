//Lowest Common Ancestor

struct LCA{
    
    int n;
    const int sz = 32;
    vector<int> marc, height;
    vector<vector<int>> g, bl;

    //Trocar se a raiz nao for 1
    LCA(int n) : n(n), g(n+1), bl(sz, vector<int> (n+1, 1)), marc(n+1), height(n+1){}

    void add_edge(int a, int b){
        g[a].push_back(b);
        g[b].push_back(a);
    }

    //Trocar se a raiz nao for 1
    void build(int x = 1){ 
        marc[x] = 1;
        for(int i = 1; i < sz; i++){
            bl[i][x] = bl[i-1][bl[i-1][x]];
        }

        for(auto viz : g[x]){
            if(marc[viz]) continue;
            bl[0][viz] = x;
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

    // Returns true if x is on the simple path between a and b
    bool entre(int x, int a, int b){
        return dist(a, b) == dist(a, x) + dist(x, b);
    }


};