//Prefix Sum 2D

struct pref2D{
    int n, m;
    vector <vector<int>> mat, pref;

    pref2D(int n, int m, vector<vector<int>> tmp){
        this-> n = n; this->m = m;
        mat = tmp;
        
        pref.resize(n+1);
        for(auto& v : pref) v.resize(m+1, 0);

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                pref[i][j] = pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1] + mat[i-1][j-1];
            }
        }
    }

    int query(int rowl, int rowr, int coll, int colr){
        rowl++, rowr++, coll++, colr++;
        if(rowl > rowr) swap(rowl, rowr);
        if(coll > colr) swap(colr, coll);
        return pref[rowr][colr] - pref[rowl-1][colr] - pref[rowr][coll-1] + pref[rowl-1][coll-1];
    }
};