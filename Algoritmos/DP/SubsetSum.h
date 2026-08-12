/**
 * Description: Subset Sum com bounded knapsack otimizado por sliding window.
 *     Soma desejada $= S$, números $= n$. Itens não podem ter valor $0$ nem frequência $0$.
 * Usage:
 *     $\text{sack}$ é um vetor de pares $\{ \text{item}, \text{frequência} \}$.
 *     $\text{dp}[x] = 1$ se é possível obter soma $x$, $0$ caso contrário.
 * Time: $O(S \sqrt{n})$ runtime, $O(n)$ memory
 * Status: tested
 */

vector<pair<int,int>> sack; // {item, frequency}
vector<int> dp(S+1, 0);
dp[0] = 1;

for(int i = 0; i < sack.size(); i++){
    vector<int> ndp(S+1);
    auto [item, freq] = sack[i];
    for(int j = 0; j < item; j++){  //starting at position j
        int numTrues = 0;
        for(int k = j; k <= S; k += item){
            ndp[k] = dp[k];
            if(numTrues > 0) ndp[k] = true;
            if(k - freq*item >= 0) numTrues -= dp[k - freq*item];
            numTrues += dp[k];
        }
    }
    swap(ndp, dp);
}
