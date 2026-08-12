/**
 * Description: Digit DP template. Exemplo: números sem dois dígitos adjacentes iguais.
 *     $\text{func}(a, b)$ retorna a quantidade de números no intervalo $[a, b]$.
 * Usage:
 *     O usuário deve modificar a condição dentro do loop em $\text{solve}$ para
 *     implementar a restrição desejada sobre os dígitos.
 * Time: $O(d \cdot 10)$ onde $d$ é o número de dígitos
 * Status: tested
 */

ll solve(string &s, int i, int tight, int last, int started){ 
    if(i==(int)s.size()) return 1;

    if(!tight && dp[i][last][started]!=-1) return dp[i][last][started];

    int lim=(tight?s[i]-'0':9);

    ll resp=0;
    for(int j=0; j<=lim; j++){
        if(started && j==last) continue;
        resp+=solve(s, i+1, tight&(j==lim), j, (started|j)>0);
    }

    if(!tight) return dp[i][last][started]=resp;
    return resp;
}

ll func(ll a, ll b){
    string agr1=to_string(a-1);
    memset(dp, -1, sizeof(dp));
    ll ans1 = solve(agr1, 0, 1, 10, 0);

    string agr2=to_string(b);
    memset(dp, -1, sizeof(dp));
    ll ans2 = solve(agr2, 0, 1, 10, 0);
    
    return ans2-ans1;
}
