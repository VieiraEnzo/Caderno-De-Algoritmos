//Matrix
//Multiplicação e Exponensiação de Matrizes
//Utilizado principalmente em recorrencias lineares
//

template<typename T> struct Matriz
{
    int n, m;
    vector<vector<T>> mat;
    const int MOD = 1e9+7;
    
    Matriz(int n, int m) : n(n), m(m), mat(n, vector<T> (m)) {}

    T* operator[](int i){
        return mat[i].data();
    }

    Matriz<T> operator*(Matriz<T> &oth){
        assert(m == oth.n);
        Matriz<T> res(n, oth.m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < oth.m; j++) { 
                res[i][j] = 0;
                for(int k = 0; k < m; k++) { 
                    res[i][j] = (res[i][j] + (mat[i][k] * 1LL * oth[k][j]) % MOD) % MOD;
                }
            }
        }
        return res;
    }

	Matriz<T> operator^(long long e){
		Matriz<T> R(n, n), b = *this;
        for(int i = 0; i < n; i++) R[i][i] = 1;
		while (e) {
			if (e&1) R = R*b;
			b = b*b;
			e >>= 1;
		}
		return R;
	}
};

using M = Matriz<int>;