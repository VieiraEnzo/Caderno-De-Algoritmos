/**
 * Description: Bridge Tree. Encontra a árvore de pontes de um grafo,
 *     onde cada aresta da árvore representa uma ponte do grafo original.
 * Time: $O(V + E)$
 * Status: tested
 */

struct BridgeTree{

    int n;
    int count = 0;
    vector<int> marc, tin, low, is_bridge;
    vector<vector<pair<int,int>>> grafo;
    vector<vector<int>> BT;
    vector<pair<int,int>> edge;

    vector<int> BTcomponent;

    BridgeTree(int n) : n(n), grafo(n+1), marc(n+1), tin(n+1), low(n+1), BTcomponent(n+1){}

    void add_edge(int a, int b){
        grafo[a].push_back({b, edge.size()});
        grafo[b].push_back({a, edge.size()});
        edge.push_back({a,b});
        is_bridge.push_back(0);
    }

    void dfs(int x, int p){
        marc[x] = 1;
        tin[x] = low[x] = ++count;
        int children = 0;
        for(auto [viz, e] : grafo[x]){
            if(viz == p) continue;
            if(marc[viz]){
                low[x] = min(low[x], tin[viz]);
            }else{
                dfs(viz,x);
                low[x] = min(low[x], low[viz]);
                if(low[viz] > tin[x]){
                    is_bridge[e] = 1;
                }
                children++;
            }
        }
    }

    void find_bridges(){
        for(ll i=1; i<=n; i++){
            if(!marc[i]) dfs(i,0);
        }   
    }

    void BTdfs(int v, int comp){
        BTcomponent[v] = comp;
        for(auto [viz, e] : grafo[v]){
            if(BTcomponent[viz] || is_bridge[e]) continue; 
            BTdfs(viz, comp);
        }
    }

    void BrigeTree(){
        int comp = 0;
        for(int i = 1; i <= n; i++){
            if(!BTcomponent[i]) BTdfs(i, ++comp);
        }

        BT.resize(comp+1);

        for(int i = 1; i <= n; i++){
            for(auto [j,e] : grafo[i]){
                if(is_bridge[e]){
                    BT[BTcomponent[i]].push_back(BTcomponent[j]);
                    BT[BTcomponent[j]].push_back(BTcomponent[i]);
                }
            }
        }
    }
};
