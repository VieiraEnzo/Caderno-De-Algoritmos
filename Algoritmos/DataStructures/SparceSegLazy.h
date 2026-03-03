// SparseSegTree with Lazy

struct SparseSegTree {
    struct Node {
        ll mn, mx, lazy;
        int l, r;
        Node() : mn(0), mx(0), lazy(0), l(-1), r(-1) {}
    };
 
    vector<Node> tree;
    ll L_BOUND, R_BOUND;
 
    SparseSegTree(ll L, ll R) {
        L_BOUND = L;
        R_BOUND = R;
        tree.reserve(15000000); 
        tree.emplace_back(); 
    }
 
    void push(int node) {
        if (tree[node].lazy != 0) {
            ll lz = tree[node].lazy;
            
            if (tree[node].l == -1) {
                tree[node].l = tree.size();
                tree.emplace_back();
            }
            if (tree[node].r == -1) {
                tree[node].r = tree.size();
                tree.emplace_back();
            }
            
            int l = tree[node].l;
            int r = tree[node].r;
            
            tree[l].mn += lz;
            tree[l].mx += lz;
            tree[l].lazy += lz;
            
            tree[r].mn += lz;
            tree[r].mx += lz;
            tree[r].lazy += lz;
            
            tree[node].lazy = 0;
        }
    }
 
    void update(int node, ll tl, ll tr, ll ql, ll qr, ll v) {
        if (ql <= tl && tr <= qr) {
            tree[node].mn += v;
            tree[node].mx += v;
            tree[node].lazy += v;
            return;
        }
        push(node);
        ll mid = tl + (tr - tl) / 2;
        
        if (ql <= mid) {
            if (tree[node].l == -1) {
                tree[node].l = tree.size();
                tree.emplace_back();
            }
            update(tree[node].l, tl, mid, ql, qr, v);
        }
        if (qr > mid) {
            if (tree[node].r == -1) {
                tree[node].r = tree.size();
                tree.emplace_back();
            }
            update(tree[node].r, mid + 1, tr, ql, qr, v);
        }
        
        ll min_val = 2e18, max_val = -2e18;
        int left_child = tree[node].l;
        int right_child = tree[node].r;
        
        if (left_child != -1) {
            min_val = min(min_val, tree[left_child].mn);
            max_val = max(max_val, tree[left_child].mx);
        } else {
            min_val = min(min_val, 0LL);
            max_val = max(max_val, 0LL);
        }
        
        if (right_child != -1) {
            min_val = min(min_val, tree[right_child].mn);
            max_val = max(max_val, tree[right_child].mx);
        } else {
            min_val = min(min_val, 0LL);
            max_val = max(max_val, 0LL);
        }
        
        tree[node].mn = min_val;
        tree[node].mx = max_val;
    }
 
    pair<ll, ll> query(int node, ll tl, ll tr, ll ql, ll qr) {
        if (ql <= tl && tr <= qr) {
            return {tree[node].mn, tree[node].mx};
        }
        push(node);
        ll mid = tl + (tr - tl) / 2;
        pair<ll, ll> res = {2e18, -2e18};
        
        if (ql <= mid) {
            if (tree[node].l != -1) {
                auto p = query(tree[node].l, tl, mid, ql, qr);
                res.first = min(res.first, p.first);
                res.second = max(res.second, p.second);
            } else {
                res.first = min(res.first, 0LL);
                res.second = max(res.second, 0LL);
            }
        }
        if (qr > mid) {
            if (tree[node].r != -1) {
                auto p = query(tree[node].r, mid + 1, tr, ql, qr);
                res.first = min(res.first, p.first);
                res.second = max(res.second, p.second);
            } else {
                res.first = min(res.first, 0LL);
                res.second = max(res.second, 0LL);
            }
        }
        return res;
    }
    void add(ll ql, ll qr, ll v) {
        update(0, L_BOUND, R_BOUND, ql, qr, v);
    }
 
    pair<ll, ll> get_minmax(ll ql, ll qr) {
        return query(0, L_BOUND, R_BOUND, ql, qr);
    }
};
