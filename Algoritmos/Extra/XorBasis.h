/**
 * Description: Xor Basis. Mantém uma base de vetores e permite reduzir um valor
 *     ao mínimo XOR com elementos da base. \texttt{mx(l)} retorna o máximo valor
 *     XOR usando elementos cujo segundo campo $\ge l$.
 * Time: $O(\log \text{MAX})$ por operação
 * Status: tested
 */

struct Basis{
  long long neutral = (1ll << 31) - 1;
  vector <pair<int, int>> basis;
  Basis(){
 
  }
  void add(pair<int, int> x){
    for(auto& i : basis){
      x.first = min(x.first, x.first^i.first);
    }
    if(x.first != 0){
      basis.push_back(x);
    }
  }
  int mx(int l){
    long long x = neutral;
    for(auto& i : basis){
      if(i.second >= l){
        x = min(x, x^i.first);
      }
    }
    return x ^ neutral;      
  }
};