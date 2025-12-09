//Lazy SegTree

struct SegTree{ 
    int n;
    struct Node{
        int val;
        Node operator+(Node other) const{
        return {this->val + other.val};
        }
        Node operator=(int x){
        return {this->val = x};
        }
    };
    Node neutral = {0};
    vector <Node> t;
    vector<int> lazy; //Change variable

    SegTree(vector <int> a){
        n = a.size();
        t.resize(4*n);
        lazy.resize(4*n); //Neutal element
        build(a, 1, 0, n-1);
    }

    void build(vector <int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = t[v*2] + t[v*2+1];
        }
    }

    void unlazy(int v, int tl, int tr){
        // if(lazy[v] == 0) return; //Neutral element

        //Update current range
        t[v].val += (tr-tl+1) * lazy[v]; 

        if(tl != tr){
            lazy[2*v] += lazy[v];   
            lazy[2*v+1] += lazy[v]; 
        }
        
        lazy[v] = 0; 
    }

    Node query(int l, int r){
        return query(1, 0, n-1, l, r);
    }

    Node query(int v, int tl, int tr, int l, int r){
        unlazy(v, tl, tr);
        if (l > r){
            return neutral;
        }
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return query(v*2, tl, tm, l, min(r, tm))
             + query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

    void update(int pos, int val){
        update(1, 0, n-1, pos, pos, val);
    }

    void update(int l, int r, int val){
        update(1, 0, n-1, l, r, val);
    }

    void update(int v, int tl, int tr, int l, int r, int val){
        unlazy(v, tl, tr);
        if (l > r){
            return;
        }
        if (l == tl && r == tr) {
            lazy[v] += val; //Change here
            unlazy(v, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        update(v*2, tl, tm, l, min(r, tm), val);
        update(v*2+1, tm+1, tr, max(l, tm+1), r, val);
        t[v] = t[2*v] + t[2*v+1];
    }

};
