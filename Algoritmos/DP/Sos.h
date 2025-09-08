//Sos DP
//
//I will be addressing the following problem: Given a fixed array A of 2N integers,
//we need to calculate forAll x function F(x) = Sum of all A[i] such that x&i = i, i.e., i is a subset of x.
//$$F[\text{mask}] = \sum_{i \subseteq \text{mask}} A[i]$$
//F[mask]=i(\subseteq)mask\sumA[i]


for(int i = 0; i<(1<<N); ++i)
	F[i] = A[i];
for(int i = 0;i < N; ++i) for(int mask = 0; mask < (1<<N); ++mask){
	if(mask & (1<<i))
		F[mask] += F[mask^(1<<i)];
}