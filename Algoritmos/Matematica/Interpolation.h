/**
 * Source: https://en.wikipedia.org/wiki/Lagrange_polynomial
 * Description: Interpolação de Lagrange. Dados $n+1$ pontos, interpola um polinômio
 *     de grau $\leq n$ e avalia em um ponto $x$.
 * Time: $O(n^2)$
 * Status: tested
 */

struct Interpolation
{
    
    //naive implementation O(n^2)
    void interpolate(vector<pair<ll,ll>> &P, int x){

        ll ans = 0;
        for(int i = 0; i < P.size(); i++){
            ll li = 1;
            for(int j = 0; j < P.size(); j++){
                if(i == j) continue;
                li *= (x - P[j].first);
                li /= (P[i].first - P[j].first);
            }
            li *= P[i].second;
            ans += li;
        }
        return ans;

    }

};
