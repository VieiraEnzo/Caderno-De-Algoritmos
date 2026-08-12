/**
 * Description: Algoritmo de Euclides Estendido. Retorna $\gcd(a, b)$,
 *     e coeficientes $x, y$ tais que $ax + by = \gcd(a, b)$.
 * Time: $O(\log(\min(a, b)))$
 * Status: tested
 */

int egcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}