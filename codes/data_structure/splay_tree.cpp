struct splay_tree {
    struct node {
        int l, r, p;
        ll key, val, cnt = 1;
        ll leftmax, rightmax, totalmax;
        bool flip_lazy, dummy;
    };

    node tree[500005]; int node_cnt = 0;
    int root = 0;

    int new_node(ll key, ll val, bool isdummy) {
        int cur = ++node_cnt;
        tree[cur].key = key; tree[cur].val = val; tree[cur].dummy = isdummy;
        return cur;
    }

    void update(int cur) {
        int l = tree[cur].l, r = tree[cur].r;
        if(l) update_lazy(l);
        if(r) update_lazy(r);

        tree[cur].cnt = 1;
        if(l) tree[cur].cnt += tree[l].cnt;
        if(r) tree[cur].cnt += tree[r].cnt;

        tree[cur].leftmax = 0;
        if(l) tree[cur].leftmax = tree[l].leftmax;
        if((!l || tree[l].leftmax == tree[l].cnt) && tree[cur].val == 1) tree[cur].leftmax = (l ? tree[l].leftmax : 0) + 1 + (r ? tree[r].leftmax : 0);

        tree[cur].rightmax = 0;
        if(r) tree[cur].rightmax = tree[r].rightmax;
        if((!r || tree[r].rightmax == tree[r].cnt) && tree[cur].val == 1) tree[cur].rightmax = (r ? tree[r].rightmax : 0) + 1 + (l ? tree[l].rightmax : 0);

        tree[cur].totalmax = 0;
        if(l) tree[cur].totalmax = max(tree[cur].totalmax, tree[l].totalmax);
        if(r) tree[cur].totalmax = max(tree[cur].totalmax, tree[r].totalmax);
        if(tree[cur].val == 1) tree[cur].totalmax = max(tree[cur].totalmax, (l ? tree[l].rightmax : 0) + 1 + (r ? tree[r].leftmax : 0));
    }
    void update_lazy(int cur) {
        if(!tree[cur].flip_lazy) return;
        swap(tree[cur].l, tree[cur].r);

        int l = tree[cur].l, r = tree[cur].r;
        if(l) {
            tree[l].flip_lazy = !tree[l].flip_lazy;
            swap(tree[l].leftmax, tree[l].rightmax);
        }
        if(r) {
            tree[r].flip_lazy = !tree[r].flip_lazy;
            swap(tree[r].leftmax, tree[r].rightmax);
        }

        tree[cur].flip_lazy = false;
    }

    void rotate(int cur) {
        int p = tree[cur].p;
        update_lazy(p); update_lazy(cur);

        if(!p) return;

        int b = 0;
        if(cur == tree[p].l) {
            tree[p].l = b = tree[cur].r;
            tree[cur].r = p;
        }
        else {
            tree[p].r = b = tree[cur].l;
            tree[cur].l = p;
        }

        tree[cur].p = tree[p].p;
        tree[p].p = cur;
        if(b) tree[b].p = p;
        if(!tree[cur].p) root = cur;
        else if(tree[tree[cur].p].l == p) tree[tree[cur].p].l = cur;
        else tree[tree[cur].p].r = cur;

        update(p); update(cur);
    }
    void splay(int cur, int nx = 0) {
        while(tree[cur].p != nx) {
            int p = tree[cur].p;
            int pp = tree[p].p;

            if(pp == nx) {
                rotate(cur);
                break;
            }

            if(pp) {
                if((cur == tree[p].l && p == tree[pp].l) || (cur == tree[p].r && p == tree[pp].r)) rotate(p);
                else rotate(cur);
            }
            rotate(cur);
        }
        if(!nx) root = cur;
    }
    int insert(ll key, ll val, bool isdummy) {
        int cur = root;
        if(cur) {
            while(1) {
                if(tree[cur].key == key) return cur;
                if(tree[cur].key > key) {
                    if(!tree[cur].l) break;
                    cur = tree[cur].l;
                }
                else {
                    if(!tree[cur].r) break;
                    cur = tree[cur].r;
                }
            }
        }

        int x = new_node(key, val, isdummy);
        if(!cur) { root = x; return x; }
        if(tree[cur].key > key) tree[cur].l = x;
        else tree[cur].r = x;
        tree[x].p = cur;
        splay(x);
        return x;
    }
    bool find(ll key) {
        int cur = root;
        if(!cur) return false;

        while(1) {
            if(tree[cur].key == key) break;
            if(tree[cur].key > key) {
                if(!tree[cur].l) break;
                cur = tree[cur].l;
            }
            else {
                if(!tree[cur].r) break;
                cur = tree[cur].r;
            }
        }
        splay(cur);
        return tree[cur].key == key;
    }
    void erase(int cur) {
        splay(cur);

        if(!tree[cur].l) {
            root = tree[cur].r;
            if(root) tree[root].p = 0;
            return;
        }
        if(!tree[cur].r) {
            root = tree[cur].l;
            tree[root].p = 0;
            return;
        }

        int l = tree[cur].l, r = tree[cur].r;
        tree[l].p = 0;

        int x = l;
        while(1) {
            update_lazy(x);
            if(!tree[x].r) break;
            x = tree[x].r;
        }
        splay(x);

        tree[x].r = r; tree[r].p = x;
        update(x);
    }

    int get_idx(int cur) {
        splay(cur);
        update_lazy(cur);
        return (tree[cur].l ? tree[tree[cur].l].cnt : 0) + 1;
    }

    void kth(int idx) {
        int cur = root;
        while(1) {
            update_lazy(cur);
            if(tree[cur].l && tree[tree[cur].l].cnt >= idx) cur = tree[cur].l;
            else {
                if(tree[cur].l) idx -= tree[tree[cur].l].cnt;
                if(--idx == 0) break;
                cur = tree[cur].r;
            }
        }
        splay(cur);
    }

    int segment(int s, int e) {
        kth(e+1);
        int tmp = root;
        kth(s-1);
        splay(tmp, root);
        return tree[tree[root].r].l;
    }

    void flip(int s, int e) {
        int node = segment(s, e);
        tree[node].flip_lazy = !tree[node].flip_lazy;
        swap(tree[node].leftmax, tree[node].rightmax);
        update(tree[root].r);
        update(root);
    }

    void print(int cur = 0) {
        if(!cur) cur = root;
        update_lazy(cur);

        if(tree[cur].l) print(tree[cur].l);
        if(!tree[cur].dummy) cout << tree[cur].val << " ";
        if(tree[cur].r) print(tree[cur].r);
    }
} S;

// CURRENT position among elements not yet erased (positions shift after an erase):
//   "1 s e" - reverse the range [s,e]
//   "2 s e" - print the longest run of 1s within [s,e]
//   "3 p"   - erase the element currently at position p
//   "4 p"   - print the current position of the element originally
//             inserted at position p
int id[100005]; // id[p] = node index of the element originally inserted at position p
void SolveProblem() {
    int n, q; cin >> n >> q;
    S.insert(0, 0, true); // left boundary dummy
    for(int i=1; i<=n; i++) { 
        ll v; cin >> v; 
        id[i] = S.insert(i, v, false); 
    }
    S.insert(n+1, 0, true); // right boundary dummy

    for(int i=1; i<=q; i++) {
        int type; cin >> type;
        if(type == 1) {
            int s, e; cin >> s >> e;
            S.flip(s+1, e+1); // +1 skips the left dummy
        }
        else if(type == 2) {
            int s, e; cin >> s >> e;
            int node = S.segment(s+1, e+1);
            cout << S.tree[node].totalmax << "\n";
        }
        else if(type == 3) {
            int p; cin >> p;
            S.kth(p+1);
            S.erase(S.root);
        }
        else {
            int p; cin >> p;
            cout << S.get_idx(id[p]) - 1 << "\n"; // -1 undoes the left-dummy offset
        }
    }
}
