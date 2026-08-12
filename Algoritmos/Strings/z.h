/**
 * Description: Z-function. $Z[i]$ é o tamanho do maior prefixo da string
 *     que começa na posição $i$ e é igual a um prefixo da string original.
 * Time: $O(n)$
 */

vector<int> zfunc(string s){
    int n = s.size();
    vector<int> z(n);
    for(int i = 1, l = 0, r = 0; i < n; i++){
        if(i <= r) z[i] = min(z[i-l], r-i+1);
        while(i + z[i] < n && s[i + z[i]] == s[z[i]]){
            z[i]++;
        }
        if(i+z[i]-1 > r){
            r = i+z[i]-1;
            l = i;
        }
    }
    return z;
}