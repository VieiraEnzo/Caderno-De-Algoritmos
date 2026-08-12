/**
 * Description: Fenwick Tree (BIT) para range sum com update pontual.
 *     Suporta função associativa com inversos em um conjunto com elemento neutro.
 *     Para máximo: apenas update de incremento (só é possível aumentar valores).
 * Time: $O(\log n)$ por query/update
 * Status: tested
 */

struct FenwickTree {
    vector<int> bit; 
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> const &a) : FenwickTree(a.size()){
        for (int i = 0; i < n; i++) {
            bit[i] += a[i];
            int r = i | (i + 1);
            if (r < n) bit[r] += bit[i];
        }
    }


    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r]; //ret = max(ret, bit[r]);
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta; //bit[idx] = max(bit[idx], delta);
    }
};
