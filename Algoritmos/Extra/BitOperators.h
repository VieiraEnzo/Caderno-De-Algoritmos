Pra fazer funcionar com long long é só colocar ll no final da função, por exemplo "_builtin_clz(x)" vira "_builtin_clzll(x)"
__builtin_clz(x): Count leading zeros. Retorna o número de zeros no início da representação binária de x (incio == bits mais significativos)
__builtin_ctz(x): Count trailing zeros. Retorna o número de zeros no final da representação binária de x
__builtin_popcount(x): Population count. Retorna o número de bits definidos como 1 na representação binária de x
__builtin_parity(x): Parity. Retorna 1 se o número de bits definidos como 1 for ímpar e 0 se for par.
int L = 32 - __builtin_clz(n), n = 1 << L; : "n" se torna a primeira potencia de 2 estritamente maior que n 
