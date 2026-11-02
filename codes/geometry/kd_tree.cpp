// 2D KD-Tree (median split, alternating axis).
// Time: build O(n log n); nearest/range query O(sqrt n) average, O(n) worst case.
struct node { pll pt; int lc, rc; };
node tree[100005]; int node_cnt = 0;
pll p[100005];

ll sqr(ll x) { return x * x; }
ll dist2(pll a, pll b) { return sqr(a.first - b.first) + sqr(a.second - b.second); }

// usage: fill p[1..n], then build(1, n, 0)
int build(int s, int e, int depth) {
    if(s > e) return 0;
    int mid = (s+e) >> 1;
    nth_element(p+s, p+mid, p+e+1, [&](pll a, pll b) {
        return depth%2 == 0 ? a.first < b.first : a.second < b.second;
    });
    int cur = ++node_cnt;
    tree[cur].pt = p[mid];
    tree[cur].lc = build(s, mid-1, depth+1);
    tree[cur].rc = build(mid+1, e, depth+1);
    return cur;
}

// nearest point to target other than an exact coordinate match with target;
// call with best={}, bestd=LLONG_MAX
void nearest(int index, int depth, pll target, pll &best, ll &bestd) {
    if(!index) return;
    ll d = dist2(tree[index].pt, target);
    if(tree[index].pt != target && d < bestd) { bestd = d; best = tree[index].pt; }

    ll diff = depth%2 == 0 ? target.first - tree[index].pt.first : target.second - tree[index].pt.second;
    int near = diff <= 0 ? tree[index].lc : tree[index].rc;
    int far = diff <= 0 ? tree[index].rc : tree[index].lc;

    nearest(near, depth+1, target, best, bestd);
    if(sqr(diff) < bestd) nearest(far, depth+1, target, best, bestd);
}

// counts points with xl<=x<=xr and yl<=y<=yr
int range_count(int index, int depth, ll xl, ll xr, ll yl, ll yr) {
    if(!index) return 0;
    ll x = tree[index].pt.first, y = tree[index].pt.second;
    int cnt = (x>=xl && x<=xr && y>=yl && y<=yr) ? 1 : 0;

    ll v = depth%2 == 0 ? x : y, lo = depth%2 == 0 ? xl : yl, hi = depth%2 == 0 ? xr : yr;
    if(lo <= v) cnt += range_count(tree[index].lc, depth+1, xl, xr, yl, yr);
    if(hi >= v) cnt += range_count(tree[index].rc, depth+1, xl, xr, yl, yr);
    return cnt;
}

// example: build once, then answer repeated nearest-neighbor queries
void solve_nearest_queries() {
    int n; cin >> n;
    for(int i=1; i<=n; i++) cin >> p[i].first >> p[i].second;
    int root = build(1, n, 0);

    int q; cin >> q;
    while(q--) {
        ll qx, qy; cin >> qx >> qy;
        pll best = {}; ll bestd = LLONG_MAX;
        nearest(root, 0, {qx, qy}, best, bestd);
        cout << best.first << " " << best.second << "\n";
    }
}

// example: build once, then answer repeated rectangle range-count queries
void solve_range_queries() {
    int n; cin >> n;
    for(int i=1; i<=n; i++) cin >> p[i].first >> p[i].second;
    int root = build(1, n, 0);

    int q; cin >> q;
    while(q--) {
        ll xl, xr, yl, yr; cin >> xl >> xr >> yl >> yr;
        cout << range_count(root, 0, xl, xr, yl, yr) << "\n";
    }
}
