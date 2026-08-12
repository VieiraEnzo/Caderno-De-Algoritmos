/**
 * Description: Dominator Tree. Computa a árvore de dominadores dos vértices alcançáveis
 *     a partir da raiz.
 * Usage: \texttt{build(r, n)} constrói a árvore de dominadores a partir da raiz \texttt{r};
 *     \texttt{t[i]} armazena os vértices da dominator tree.
 * Time: $O((V+E)\log V)$
 */

const int N = 2e5 + 9;

vector<int> g[N];
vector<int> t[N], rg[N], bucket[N]; //t = dominator tree of the nodes reachable from root
int sdom[N], par[N], idom[N], dsu[N], label[N];
int id[N], rev[N], T;
int find_(int u, int x = 0) {
  if(u == dsu[u]) return x ? -1 : u;
  int v = find_(dsu[u], x+1);
  if(v < 0)return u;
  if(sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
  dsu[u] = v;
  return x ? v : label[u];
}

void dfs(int u) {
  T++; id[u] = T;
  rev[T] = u; label[T] = T;
  sdom[T] = T; dsu[T] = T;
  for(int i = 0; i < g[u].size(); i++) {
    int w = g[u][i];
    if(!id[w]) dfs(w), par[id[w]] = id[u];
    rg[id[w]].push_back(id[u]);
  }
}

void build(int r, int n) {
  dfs(r);
  n = T;
  for(int i = n; i >= 1; i--) {
    for(int j = 0; j < rg[i].size(); j++) sdom[i] = min(sdom[i], sdom[find_(rg[i][j])]);
    if(i > 1) bucket[sdom[i]].push_back(i);
    for(int j = 0; j < bucket[i].size(); j++) {
      int w = bucket[i][j];
      int v = find_(w);
      if(sdom[v] == sdom[w]) idom[w] = sdom[w];
      else idom[w] = v;
    }
    if(i > 1) dsu[i] = par[i];
  }
  for(int i = 2; i <= n; i++) {
    if(idom[i] != sdom[i]) idom[i]=idom[idom[i]];
    t[rev[i]].push_back(rev[idom[i]]);
    t[rev[idom[i]]].push_back(rev[i]);
  }
}

int st[N], en[N];
void yo(int u, int pre = 0) {
  st[u] = ++T;
  for(auto v: t[u]) {
    if(v == pre) continue;
    yo(v, u);
  }
  en[u] = T;
}