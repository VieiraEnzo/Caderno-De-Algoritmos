/**
 * Description: Hash polinomial de strings módulo $MOD$. Constrói em $O(n)$
 *     e permite consultas em $O(1)$.
 * Usage: getRange(a, b) retorna o hash da substring $[a, b)$ (0-indexado).
 * Time: $O(n)$ build, $O(1)$ query
 * Status: tested
 */

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
const ll B = uniform_int_distribution<ll>(0, M - 1)(rng);

template<int MOD> struct Hashing{
    ll base, n;
    vector<ll> pow, ha; 

    Hashing(string & s, int a) : n(s.size()), base(a) ,pow(n+1), ha(n+1){

        pow[0] = 1;
        for(int i = 0; i < n; i++){
            ha[i+1] = (ha[i] * base + s[i])%MOD;
            pow[i+1] = (pow[i] * base)%MOD;
        }
    }
    
    int getRange(int a, int b){
        assert(a <= b);
        ll hash =  (ha[b] - (ha[a] * pow[b-a])%MOD)%MOD;
        return hash < 0 ? hash + MOD : hash;
    }
    
};