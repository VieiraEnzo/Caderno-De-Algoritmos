/**
 * Source: Simon Lindholm
 * Description: Busca ternária para funções discretas e contínuas.
 *     Encontra o menor $i \in [a, b]$ que maximiza $f(i)$, assumindo
 *     $f(a) < \dots < f(i) \ge \dots \ge f(b)$. Para minimizar,
 *     inverter as desigualdades. Para reais, usar $\approx 200$--$300$ iterações.
 * Usage:
 *     \texttt{int ind = ternSearch(0, n-1, [\&](int i)\{ return a[i]; \});}
 * Time: $O(\log(b - a))$
 * Status: tested
 */

double ternary(double l, double r){
    // < for maximum and > for minimum value
    int cont = 300;
    while (cont --)
    {
        double m1 = l + (r-l)/3;
        double m2 = r - (r-l)/3;
        double f1 = f(m1);
        double f2 = f(m2);
        if(f1>f2){
            l = m1;
        }else{
            r = m2;
        }
    }
    return l;
}

/**
 * Author: Simon Lindholm
 * Date: 2015-05-12
 * License: CC0
 * Source: own work
 * Description:
 * Find the smallest i in $[a,b]$ that maximizes $f(i)$, assuming that $f(a) < \dots < f(i) \ge \dots \ge f(b)$.
 * To reverse which of the sides allows non-strict inequalities, change the < marked with (A) to <=, and reverse 
 * the loop at (B).
 * To minimize $f$, change it to >, also at (B).
 * If you are dealing with real numbers, you'll need to pick $m_1 = (2a + b)/3.0$ and $m_2 = (a + 2b)/3.0$. 
 * Consider setting a constant number of iterations for the search, usually $[200,300]$ iterations are sufficient
 * for problems with error limit as $10^{-6}$.
 * Status: tested
 * Usage: int ind = ternSearch(0,n-1,[\&](int i){return a[i];});
 * Time: O(\log(b-a))
 */

int ternSearch(int a, int b) {
	assert(a <= b);
	while (b - a >= 5) {
		int mid = (a + b) / 2;
		if (f(mid) < f(mid+1)) a = mid; // (A)
		else b = mid+1;
	}
	for(int i = a+1; i <= b; ++i) 
		if (f(a) < f(i)) a = i; // (B)
	return a;
}
