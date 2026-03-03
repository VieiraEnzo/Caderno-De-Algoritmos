//GCD convolution

vector<int> PrimeEnumerate(int n) {
	vector<int> P; vector<bool> B(n + 1, 1);
	for (int i = 2; i <= n; i++) {
		if (B[i]) P.push_back(i);
		for (int j : P) { if (i * j > n) break; B[i * j] = 0; if (i % j == 0) break; }
	}
	return P;
}
template<typename T>
void MultipleZetaTransform(vector<T>& v) {
	const int n = (int)v.size() - 1;
	for (int p : PrimeEnumerate(n)) {
		for (int i = n / p; i; i--)
			v[i] += v[i * p];
	}
}
template<typename T>
void MultipleMobiusTransform(vector<T>& v) {
	const int n = (int)v.size() - 1;
	for (int p : PrimeEnumerate(n)) {
		for (int i = 1; i * p <= n; i++)
			v[i] -= v[i * p];
	}
}
template<typename T>
vector<T> GCDConvolution(vector<T> A, vector<T> B) {
    MultipleZetaTransform(A);
    MultipleZetaTransform(B);
    for (int i = 0; i < A.size(); i++) A[i] *= B[i];
    MultipleMobiusTransform(A);
    return A;
}