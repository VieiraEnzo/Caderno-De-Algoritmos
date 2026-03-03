//Topo Sort
//Algorithm to find the topological sort of a directed acyclic graph (DAG).
//It returns a vector with the vertices in topological order.
//Complexity: O(n + m), where n is the number of vertices and m is the number of edges.
struct TopoSort
{
    int n;
    vector<int> grau;
    vector<vector<int>> grafo;

    TopoSort(int n): n(n), grau(n+1), grafo(n+1){}
    
    void add_edge(int a, int b){
        grau[b]++;
        grafo[a].push_back(b);
    }
    
    vector<int> top_sort(){
        vector<int> resp;
        queue<int> fila;
        for(int i=1; i<=n;i++){
            if(!grau[i])fila.push(i);
        }
        while (!fila.empty())
        {
            int u = fila.front();
            resp.push_back(u);
            fila.pop();
            for(int viz : grafo[u]){
                grau[viz]--;
                if(!grau[viz])fila.push(viz);
            }   
        }
        if(resp.size() < n){
            return {};
        }else{
            return resp;
        }
    }
};
