/**
 * Author: Enzo Fernandes Vieira
 * Source: 
 * Description: BFS porque o caio não sabe codar 
 * Usage: 
 * Skip: true
 * Time: $O(N)$.
 * Status: Não
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