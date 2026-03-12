//Matrix
//Multiplicação e Exponensiação de Matrizes
//Tested: NO

template<typename T> struct Matriz
{
    int n, m;
    vector<vector<T>> mat;

    static constexpr T add_id() { return 0; } //Neutral element of adition
    static constexpr T mul_id() { return 1; } //Neutral element of multiplication

    Matriz(int n, int m) : n(n), m(m), mat(n, vector<T> (m, add_id())) {}

    const T* operator[](int i) const { return mat[i].data(); }
    T* operator[](int i) { return mat[i].data(); }

    Matriz<T> operator*(const Matriz<T> &oth) const {
        assert(m == oth.n);
        Matriz<T> res(n, oth.m);
        for(int i = 0; i < n; i++) {
            for(int k = 0; k < m; k++) { 
                T val = mat[i][k]; 
                for(int j = 0; j < oth.m; j++) { 
                    // Add modulo here if the problem requires it:
                    // res[i][j] = (res[i][j] + val * 1LL * oth[k][j]) % MOD;
                    res[i][j] += val * oth[k][j];
                }
            }
        }
        return res;
    }

    Matriz<T> operator^(long long e) const {
        assert(n == m);
        Matriz<T> R(n, n), b = *this;
        for(int i = 0; i < n; i++) R[i][i] = mul_id();
        while (e > 0) {
            if (e & 1) R = R * b;
            b = b * b;
            e >>= 1;
        }
        return R;
    }
};

using M = Matriz<int>;
