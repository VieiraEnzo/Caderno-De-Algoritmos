/**
 * Description: Sum over Subsets (SOS) DP.
 *     Dado um array $A$ de $2^N$ inteiros, calcula $F[\text{mask}] = \sum_{i \subseteq \text{mask}} A[i]$.
 * Time: $O(N \cdot 2^N)$
 * Status: tested
 */

for(int i = 0; i<(1<<N); ++i)
	F[i] = A[i];
for(int i = 0;i < N; ++i) for(int mask = 0; mask < (1<<N); ++mask){
	if(mask & (1<<i))
		F[mask] += F[mask^(1<<i)];
}