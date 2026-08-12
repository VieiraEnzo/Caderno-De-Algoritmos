/**
 * Description: Dados $n$ pontos $(x[i], y[i])$, computa um polinômio de grau $n-1$ que
 *     passa por eles: $p(x) = a[0]x^0 + \dots + a[n-1]x^{n-1}$.
 *     Para precisão numérica, use $x[k] = c \cdot \cos(k/(n-1) \cdot \pi), k = 0 \dots n-1$.
 * Time: $O(n^2)$
 */
typedef vector<double> vd;
vd interpolate(vd x, vd y, int n) {
	vd res(n), temp(n);
	for(int k = 0; k < n-1; ++k) for(int i = k+1; i < n; ++i)
		y[i] = (y[i] - y[k]) / (x[i] - x[k]);
	double last = 0; temp[0] = 1;
	for(int k = 0; k < n; ++k) for(int i = 0; i < n; ++i) {
		res[i] += y[k] * temp[i]; swap(last, temp[i]);
		temp[i] -= last * x[k];
	}
	return res;
}