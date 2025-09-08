//Interpolação Pts -> Pt
// https://en.wikipedia.org/wiki/Lagrange_polynomial
// 
// Interpolação is a numerical method to 
// know the result of a function of degree n 
// just by knowing  n+1 point from it
//
//
// Proof of Uniques: say we have another polynome
// of degree <=k M(x). So in M(x) - L(x) = 0 in k+1
// points, but the only function that has K+1 roots
// with degree <=k is f(x) = 0, so
// M(x) - L(X) = 0 -> M(x) = L(x)

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
