/**
 * Description: Busca em largura (BFS) em grafos.
  * Description: BFS porque o caio não sabe codar 

 * Skip: true
 * Time: $O(N)$
 */

queue<int> q;
vector<bool> used(n);

q.push(s);
used[s] = true;
while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int u : adj[v]) {
        if (!used[u]) {
            used[u] = true;
            q.push(u);
        }
    }
}