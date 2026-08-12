/**
 * Description: Compressão de coordenadas. Mapeia valores de um array para
 *     inteiros consecutivos $[0, k)$, preservando a ordem relativa.
 * Usage: Para recuperar o valor original: \texttt{d[arr[i]]}.
 * Skip: true
 * Time: $O(N \log N)$
 */

vector<int> d = arr;
sort(d.begin(), d.end());
d.resize(unique(d.begin(), d.end()) - d.begin());
for (int i = 0; i < n; ++i) {
    arr[i] = lower_bound(d.begin(), d.end(), arr[i]) - d.begin();
}
