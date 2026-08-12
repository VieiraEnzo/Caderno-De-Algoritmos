/**
 * Source: Simon Lindholm
 * Description: Container onde é possível adicionar retas da forma $kx+m$ e
 *     consultar o valor máximo em pontos $x$. Útil para DP (convex hull trick).
 * Time: $O(\log n)$ por operação
 * Status: stress-tested
 */

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
}; 

struct LineContainer : multiset<Line, less<>> {

	static const ll inf = LLONG_MAX; //for doubles 1/.0
	
    ll div(ll a, ll b) { //for doubles return a/b
		return a / b - ((a ^ b) < 0 && a % b); }

	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	} 
	
    //para achar o mínimo, é preciso fazer insert({-k, -m, 0}), além disso multiplicar por -1 o resultado da query
    void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) 
			isect(x, erase(y));
	}

	ll query(ll x) {
		assert(!empty());
        auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};