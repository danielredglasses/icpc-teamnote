const ll X_MIN = -1e9, X_MAX = 1e9, NEG = -4e18;

struct line {
    ll a, b;
    line() : a(0), b(NEG) { }
    line(ll _a, ll _b) : a(_a), b(_b) { }
    ll get(ll x) { return a * x + b; }
};

struct node {
    int l, r;
    line mx;
};

node tree[1000005]; int node_cnt = 0;
int root;

void add_line(int index, ll l, ll r, line cur_line) {
    line down = tree[index].mx, up = cur_line;
    if(down.get(l) > up.get(l)) swap(down, up);

    if(up.get(r) >= down.get(r)) {
        tree[index].mx = up;
        return;
    }

    ll mid = (l+r) >> 1;
    if(up.get(mid) > down.get(mid)) {
        tree[index].mx = up;
        if(!tree[index].r) tree[index].r = ++node_cnt;
        add_line(tree[index].r, mid+1, r, down);
    }
    else {
        tree[index].mx = down;
        if(!tree[index].l) tree[index].l = ++node_cnt;
        add_line(tree[index].l, l, mid, up);
    }
}

ll find_mx(int index, ll l, ll r, ll x) {
    if(!index) return NEG;
    ll mid = (l+r) >> 1, mx = tree[index].mx.get(x);
    if(x <= mid) return max(mx, find_mx(tree[index].l, l, mid, x));
    return max(mx, find_mx(tree[index].r, mid+1, r, x));
}

void SolveProblem() {
    root = ++node_cnt;
    add_line(root, X_MIN, X_MAX, line(a, b));
    cout << find_mx(root, X_MIN, X_MAX, x) << "\n";
}
