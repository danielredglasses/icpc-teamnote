struct link_cut {
    struct node {
        int l, r, p; 
        ll key, val;
        pll mx = {-1e18, -1e18};
        bool flip_lazy;
    };

    node tree[100005]; int sz = 0; 

    void init(int _sz) {
        sz = _sz;
        for(int i=1; i<=sz; i++) tree[i].key = i;
    }

    bool is_root(int cur) {
        int p = tree[cur].p;
        return !p || (cur != tree[p].l && cur != tree[p].r);
    }
    bool is_left(int cur) {
        int p = tree[cur].p;
        return p && cur == tree[p].l;
    }

    void update(int cur) {
        tree[cur].mx = {tree[cur].val, tree[cur].key};
        if(tree[cur].l) tree[cur].mx = max(tree[cur].mx, tree[tree[cur].l].mx);
        if(tree[cur].r) tree[cur].mx = max(tree[cur].mx, tree[tree[cur].r].mx);
    }

    void update_lazy(int cur) {
        if(!tree[cur].flip_lazy) return;
        swap(tree[cur].l, tree[cur].r);

        if(tree[cur].l) tree[tree[cur].l].flip_lazy ^= 1;
        if(tree[cur].r) tree[tree[cur].r].flip_lazy ^= 1;
        tree[cur].flip_lazy = false;
    }

    void rotate(int cur) {
        int p = tree[cur].p;
        if(is_left(cur)) {
            if(tree[cur].r) tree[tree[cur].r].p = p;
            tree[p].l = tree[cur].r; tree[cur].r = p;
        }
        else {
            if(tree[cur].l) tree[tree[cur].l].p = p;
            tree[p].r = tree[cur].l; tree[cur].l = p;
        }

        if(!is_root(p)) {
            if(is_left(p)) tree[tree[p].p].l = cur;
            else tree[tree[p].p].r = cur;
        }

        tree[cur].p = tree[p].p; tree[p].p = cur;
        update(p); update(cur);
    }

    void splay(int cur) {
        while(!is_root(cur)) {
            int p = tree[cur].p;
            if(!is_root(p)) update_lazy(tree[p].p);
            update_lazy(p); update_lazy(cur);

            if(!is_root(p)) {
                if(is_left(cur) == is_left(p)) rotate(p);
                else rotate(cur);
            }

            rotate(cur);
        }
        update_lazy(cur);
    }
    void access(int cur) {
        splay(cur); tree[cur].r = 0;
        update(cur);

        for(int y=cur; tree[cur].p; splay(cur)) {
            y = tree[cur].p; splay(y);
            tree[y].r = cur; update(y);
        }
    }

    void link(int p, int c) {
        access(c); access(p);
        tree[c].l = p; tree[p].p = c;
        update(c);
    }

    void cut(int cur) {
        access(cur);
        if(!tree[cur].l) return;
        tree[tree[cur].l].p = 0; tree[cur].l = 0;
        update(cur);
    }
    void cut(int a, int b) {
        if(find_parent(a) == b) cut(a);
        else cut(b);
    }

    int find_root(int cur) {
        access(cur);
        while(tree[cur].l) {
            cur = tree[cur].l;
            update_lazy(cur);
        }
        splay(cur);
        return cur;
    }
    int find_parent(int cur) {
        access(cur);
        if(!tree[cur].l) return 0;
        cur = tree[cur].l; update_lazy(cur);
        while(tree[cur].r) {
            cur = tree[cur].r;
            update_lazy(cur);
        }
        splay(cur);
        return cur;
    }
    int find_lca(int a, int b) {
        access(a); access(b);
        splay(a);
        return tree[a].p ? tree[a].p : a;
    }

    void update_node(int cur, ll val) {
        splay(cur);
        tree[cur].val = val;
        update(cur);
    }

    pll query(int a, int b) {
        int lca = find_lca(a, b);

        pll mx = {tree[lca].val, tree[lca].key};

        access(a); splay(lca);
        if(tree[lca].r) mx = max(mx, tree[tree[lca].r].mx);

        access(b); splay(lca);
        if(tree[lca].r) mx = max(mx, tree[tree[lca].r].mx);

        return mx;
    }

    void reroot(int cur) {
        access(cur); splay(cur);
        tree[cur].flip_lazy ^= 1;
    }

    bool is_connect(int a, int b) { return find_root(a) == find_root(b); }
} S;

void SolveProblem() {
    int n, q; cin >> n >> q;
    S.init(n);
    for(int i=1; i<=n; i++) { 
        ll v; cin >> v; 
        S.update_node(i, v); 
    }

    for(int i=1; i<=q; i++) {
        int type; cin >> type;
        if(type == 1) {
            int a, b; cin >> a >> b;
            S.reroot(b);
            S.link(a, b);
        }
        else if(type == 2) {
            int a, b; cin >> a >> b;
            S.cut(a, b);
        }
        else if(type == 3) {
            int a; ll v; cin >> a >> v;
            S.update_node(a, v);
        }
        else {
            int a, b; cin >> a >> b;
            if(!S.is_connect(a, b)) cout << -1 << "\n";
            else cout << S.query(a, b).first << "\n";
        }
    }
}
