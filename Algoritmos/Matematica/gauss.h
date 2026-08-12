/**
 * Description: Eliminação de Gauss para resolver sistemas lineares.
 *     Retorna $(num\_solucoes, solucao)$. $0$ = sem solução, $1$ = única, $INF$ = infinitas.
 * Time: $O(n^3)$, onde $n$ é o número de variáveis
 */

template<typename T>
pair<int, vector<T>> gauss(vector<vector<T>> a, vector<T> b) {
	const double eps = 1e-6;
	int n = a.size(), m = a[0].size();
	for (int i = 0; i < n; i++) a[i].push_back(b[i]);

	vector<int> where(m, -1);
	for (int col = 0, row = 0; col < m and row < n; col++) {
		int sel = row;
		for (int i=row; i<n; ++i)
			if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
		if (abs(a[sel][col]) < eps) continue;
		for (int i = col; i <= m; i++)
			swap(a[sel][i], a[row][i]);
		where[col] = row;

		for (int i = 0; i < n; i++) if (i != row) {
			T c = a[i][col] / a[row][col];
			for (int j = col; j <= m; j++)
				a[i][j] -= a[row][j] * c;
		}
		row++;
	}

	vector<T> ans(m, 0);
	for (int i = 0; i < m; i++) if (where[i] != -1)
		ans[i] = a[where[i]][m] / a[where[i]][i];
	for (int i = 0; i < n; i++) {
		T sum = 0;
		for (int j = 0; j < m; j++)
			sum += ans[j] * a[i][j];
		if (abs(sum - a[i][m]) > eps)
			return pair(0, vector<T>());
	}

	for (int i = 0; i < m; i++) if (where[i] == -1)
		return pair(INF, ans);
	return pair(1, ans);
}