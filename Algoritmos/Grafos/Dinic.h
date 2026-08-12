/**
 * Description: Dinic para fluxo máximo.
 *     Grafo com capacidades 1: $O(\min(M \sqrt{M}, M N^{2/3}))$.
 *     Todo vértice tem grau de entrada ou saída 1 e a maior capacidade é 1: O(sqrt(N)*M)
 *     \texttt{recap()} retorna as arestas do min-cut.
 * Time: $O(\min(V \cdot \text{max\_flow}, V^2 E))$
 * Status: tested
 */

template<typename T>
struct Dinic{
    struct Edge {int v, u; T cap, flow;};
    int m=0;
    vector<Edge> edges;
    vector<vector<int> > vec;
    vector<int> lv, pos;
    queue<int> fila;

    Dinic() {}
 
    Dinic(int n) : vec(n), lv(n), pos(n) {}
 
    void add_edge(int v, int u, T cap) {
        edges.push_back({v, u, cap, 0});
        edges.push_back({u, v, 0, 0});
        vec[v].push_back(m);
        vec[u].push_back(m+1);
        m+=2;
    }
 
    int bfs(int t){
        while(!fila.empty()){
            int v=fila.front();
            fila.pop();
            for(int i:vec[v]){
                if(edges[i].cap-edges[i].flow<1) continue;
                if(lv[edges[i].u]!=-1) continue;
 
                lv[edges[i].u]=lv[v]+1;
                fila.push(edges[i].u);
            }
        }
        return lv[t]!=-1;
    }
 
    T dfs(int v, int t, T menor) {
        if(!menor) return 0;
        if(v==t) return menor;
 
        for(int& j=pos[v]; j<(int)vec[v].size(); j++){
            int i=vec[v][j];
            int u=edges[i].u;
 
            if(lv[v]+1!=lv[u] || edges[i].cap-edges[i].flow<1) continue;
 
            T agr=dfs(u, t, min(menor, edges[i].cap-edges[i].flow));
            if(!agr) continue;
 
            edges[i].flow+=agr;
            edges[i^1].flow-=agr;
 
            return agr;
        }
        return 0;
    }
 
    T max_flow(int s, int t){
        T flow=0;
        while(1){
            fill(lv.begin(), lv.end(), -1);
 
            lv[s]=0;
            fila.push(s);
 
            if(!bfs(t)) break;
 
            fill(pos.begin(), pos.end(), 0);
 
            while(T atual=dfs(s, t, INF)) flow+=atual; //remember to change INF
        }
        return flow;
    }
    auto recap(){
        vector<pair<int, int> > resp;
        for(int i=0; i<(int)edges.size(); i+=2){
            if(lv[edges[i].v]>=0 && lv[edges[i].u]==-1) resp.push_back({edges[i].v, edges[i].u});
        }
        return resp;
    }
};