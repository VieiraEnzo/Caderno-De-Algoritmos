//Floyd Warshall
//
//Algoritmo todos para todos de distancia mínima
//Se houver ciclos negativos, para algum vertice a  -> dist[a][a] < 0
//Complexidade: O(n^3)

struct FloydWarshall
{   

    const int MAXN = 500;
    cont ll INF = 1e18;
    vector dist(maxn, vector<ll>(maxn, INF));

    void floydWarshall( ){

        for(int i = 0; i < MAXN; i++)dist[i][i] = 0;

        for(int k = 1; k < MAXN; k++)
            for(int i = 1; i < MAXN; i++)
                for(int j = 1; j < MAXN; j++){
                    if(dist[i][k] < INF && dist[k][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            
    }


};
