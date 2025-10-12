//Fast Subset Transform
/**
 * Author: Lucian Bicsi
 * Description: Transform to a basis with fast convolutions of the form
 * $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$,
 * where $\oplus$ is one of AND, OR, XOR. The size of $a$ must be a power of two.
 * Time: O(N \log N)
 * Também chamada de Transformada Rápida de Walsh-Hadamard
 */

void FST(vector<int> &a, bool inv) {
	for (int n = a.size(), step = 1; step < n; step *= 2) {
		for (int i = 0; i < n; i += 2 * step) for(int j = i; j < i+step; ++j) {
			int &u = a[j], &v = a[j + step]; tie(u, v) =
				inv ? pii(v - u, u) : pii(v, u + v); // AND
				inv ? pii(v, u - v) : pii(u + v, u); // OR
				pii(u + v, u - v);                   // XOR
		}
	}
	if (inv) for(auto &x : a) x /= a.size(); // XOR only
}
vector<int> conv(vector<int> a, vector<int> b) {
	FST(a, 0); FST(b, 0);
	for(int i = 0; i < a.size(); ++i) a[i] *= b[i];
	FST(a, 1); return a;
}