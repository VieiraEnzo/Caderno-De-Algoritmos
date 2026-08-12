/**
 * Description: 2-SAT solver. Resolve equações do tipo $(a \lor b) \land (c \lor d) \dots$
 *     Cláusula $(+a \lor -b)$ vira \texttt{add\_edge(1, a, 0, b)}.
 * Usage: \texttt{add\_edge(1, a, 0, b)} para $(+a \lor -b)$.
 * Time: $O(n + m)$, onde $n$ = variáveis, $m$ = implicações
 * Status: tested -- \url{https://cses.fi/problemset/result/8784228/}
 */

struct SAT2{

    int n, cont;
    vector<char> resp;
    vector<int> marc, ord, comp;
    vector<vector<int>> grafo, rgrafo,scc;

    SAT2(int n) :  n(n), marc(2*n+2), grafo(2*n+2), rgrafo(2*n+2), comp(2*n+2), resp(2*n + 2){}

    void add_edge(int sx, int x, int sy, int y){ // '+' = 1, '-' = 0
        
        grafo[y+n*(!sy)].push_back(x+n*sx); //~y -> x
        grafo[x+n*(!sx)].push_back(y+n*sy); //~x -> y

        rgrafo[x+n*sx].push_back(y+n*(!sy)); 
        rgrafo[y+n*sy].push_back(x+n*(!sx));
        
    }

    void dfs1(int v){   
        marc[v] = 1;
        for(auto viz : grafo[v]){
            if(!marc[viz]) dfs1(viz);
        }
        ord.push_back(v);
    }

    void dfs2(int v, int c){
        comp[v] = c;
        for(auto viz : rgrafo[v]){
            if(!comp[viz]) dfs2(viz, c);
        } 
    }

    void build(){

        cont = 0;

        for(int i = 1; i <=2*n ;i++){
            if(!marc[i]) dfs1(i);
        }

        reverse(ord.begin(), ord.end());

        for(int v : ord){
            if(!comp[v]){
                dfs2(v, ++cont);
            }
        }

        bool can = true;
        for(int i= 1; i <=n; i++){
            if(comp[i] == comp[i+n]) can = false;
            resp[i]=comp[i]<comp[i+n]?'+':'-'; 
            //positiva é comp[i+n], está escolhendo a variavel que não
            //tem um caminho de implicação que resulta em impossivel
        }

        if(can){
            for(int i = 1; i <=n; i++){
                cout << resp[i] << " ";
            }
        }else{
            cout << "IMPOSSIBLE" << endl;
        }
    }

};