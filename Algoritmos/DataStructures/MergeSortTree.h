/**
 * Description: Nó de SegTree para Merge Sort Tree. Cada nó armazena um vetor ordenado.
 *     O operador \texttt{+} faz merge de dois vetores ordenados.
 * Time: $O(n \log n)$ build, $O(\log^2 n)$ por query
 */

//Segtree node for Merge-Sort
struct Node{
    vector<int> vec;
    Node operator+(Node other) const{
        vector<int> novo(vec.size() + other.vec.size());
        merge(vec.begin(), vec.end(), other.vec.begin(), other.vec.end(), novo.begin());
        return {novo};
    }
    Node operator=(int x){
    return {this->vec = {x}};
    }
};
