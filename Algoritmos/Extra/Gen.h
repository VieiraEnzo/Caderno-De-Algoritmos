/**
 * Description: Template de gerador de testes aleatórios usando \texttt{mt19937}.
 *     Gera valores inteiros uniformemente distribuídos em um intervalo.
 * Time: N/A
 * Status: tested
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

int main(){

    cin.tie(0), ios_base::sync_with_stdio(false);
    int n = uniform_int_distribution<int> (1, 3)(rng);
}