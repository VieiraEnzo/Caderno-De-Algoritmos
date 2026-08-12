/**
 * Description: Segment Tree genérica com operação associativa.
 *     Definir struct Node com \texttt{operator+} e \texttt{operator=}.
 * Time: $O(\log n)$ por query/update
 * Status: tested
 */

struct SegTree{
  int n;
  struct Node{
    int val;
    Node operator+(Node other) const{
      return {this->val + other.val};
    }
    Node operator=(int x){
      return {this->val = x};
    }
  };
  Node neutral = {0};
  vector <Node> t;

  SegTree(vector <int> a){
    n = a.size();
    t.resize(4*n);
    build(a, 1, 0, n-1);
  }

  void build(vector <int>& a, int v, int tl, int tr) {
    if (tl == tr) {
      t[v] = a[tl];
    } else {
      int tm = (tl + tr) / 2;
      build(a, v*2, tl, tm);
      build(a, v*2+1, tm+1, tr);
      t[v] = t[v*2] + t[v*2+1];
    }
  }

  Node query(int l, int r){
    return query(1, 0, n-1, l, r);
  }

  Node query(int v, int tl, int tr, int l, int r){
    if (l > r) 
      return neutral;
    if (l == tl && r == tr) {
      return t[v];
    }
    int tm = (tl + tr) / 2;
    return query(v*2, tl, tm, l, min(r, tm))
      + query(v*2+1, tm+1, tr, max(l, tm+1), r);
  }

  void update(int pos, int val){
    update(1, 0, n-1, pos, val);
  }

  void update(int v, int tl, int tr, int pos, int new_val){
    if (tl == tr) {
      t[v] = new_val;
    } else {
      int tm = (tl + tr) / 2;
      if (pos <= tm)
        update(v*2, tl, tm, pos, new_val);
      else
        update(v*2+1, tm+1, tr, pos, new_val);
      t[v] = t[v*2] + t[v*2+1];
    }
  }
};