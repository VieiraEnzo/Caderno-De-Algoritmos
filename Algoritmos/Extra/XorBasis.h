//Xor Basis

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