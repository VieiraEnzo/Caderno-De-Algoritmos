/**
 * Description: Crivo (Sieve) + Fatoração. Precomputa primos e menor divisor primo.
 *     $factorize(n)$ retorna os fatores primos de $n$ com suas frequências.
 * Time: $O(n \log \log n)$ para o crivo, $O(\log n)$ por fatoração
 * Status: tested
 */

struct Sieve{
    int maxn;
    vector <int> is_prime, min_div;
    Sieve(int n){
        this->maxn = n;
        is_prime.assign(n+1, 1);
        min_div.resize(n+1);

        for(int i = 0; i <= n; i++)
            min_div[i] = i;

        is_prime[0] = is_prime[1] = 0;
        for (int i = 2; i <= n; i++) {
            if (is_prime[i] && (long long)i * i <= n) {
                for (int j = i * i; j <= n; j += i){
                    if(is_prime[j]) min_div[j] = i;
                    is_prime[j] = false;
                }
            }
        }
    }

    vector<pair<int,int>> factorize(int n){
        assert(n <= maxn);
        vector <pair<int,int>> fact;
        while(n > 1){
            if(fact.empty() || fact.back().first != min_div[n]){
                fact.push_back({min_div[n], 1});
            }else{
                fact.back().second += 1;
            }
            n /= min_div[n];
        }
        return fact;
    }
};