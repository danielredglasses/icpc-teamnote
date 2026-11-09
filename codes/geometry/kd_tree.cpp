// 2D KD-Tree (median split, alternating axis) with lazy deletion, point ids and subtree min id.
// Time: build O(n log n); erase_id O(log n); nearest/range query O(sqrt n) average, O(n) worst case.
struct node { pll pt; int lc, rc, par, id, sz, mn; ll x1, x2, y1, y2; bool del; };
node tree[250005]; int node_cnt = 0;
pll p[250005]; int ord[250005], pos[250005];

ll sqr(ll x) { return x * x; }
ll dist2(pll a, pll b) { return sqr(a.first - b.first) + sqr(a.second - b.second); }

void pull(int index) {
    node &t = tree[index];
    t.sz = !t.del + tree[t.lc].sz + tree[t.rc].sz;
    t.mn = min({t.del ? INT_MAX : t.id, tree[t.lc].mn, tree[t.rc].mn});
}

int build(int s, int e, int depth, int par = 0) {
    tree[0].mn = INT_MAX;
    if(s > e) return 0;
    int mid = (s+e) >> 1;
    nth_element(ord+s, ord+mid, ord+e+1, [&](int a, int b) {
        return depth%2 == 0 ? p[a].first < p[b].first : p[a].second < p[b].second;
    });
    int cur = ++node_cnt;
    node &t = tree[cur];
    t.id = ord[mid]; t.pt = p[t.id]; t.par = par; t.del = false; pos[t.id] = cur;
    t.lc = build(s, mid-1, depth+1, cur);
    t.rc = build(mid+1, e, depth+1, cur);
    t.x1 = t.x2 = t.pt.first; t.y1 = t.y2 = t.pt.second;
    for(int c : {t.lc, t.rc}) if(c) {
        t.x1 = min(t.x1, tree[c].x1); t.x2 = max(t.x2, tree[c].x2);
        t.y1 = min(t.y1, tree[c].y1); t.y2 = max(t.y2, tree[c].y2);
    }
    pull(cur);
    return cur;
}

bool erase(int index, int depth, pll pt) {
    if(!index || !tree[index].sz) return false;
    bool ok = false;
    if(!tree[index].del && tree[index].pt == pt) { tree[index].del = true; ok = true; }
    else {
        ll v = depth%2 == 0 ? tree[index].pt.first : tree[index].pt.second;
        ll t = depth%2 == 0 ? pt.first : pt.second;
        if(t <= v) ok = erase(tree[index].lc, depth+1, pt);
        if(!ok && t >= v) ok = erase(tree[index].rc, depth+1, pt);
    }
    if(ok) pull(index);
    return ok;
}

void erase_id(int id) {
    int cur = pos[id];
    if(tree[cur].del) return;
    tree[cur].del = true;
    for(; cur; cur = tree[cur].par) pull(cur);
}

void nearest(int index, int depth, pll target, pll &best, ll &bestd) {
    if(!index || !tree[index].sz) return;
    ll d = dist2(tree[index].pt, target);
    if(!tree[index].del && tree[index].pt != target && d < bestd) { bestd = d; best = tree[index].pt; }

    ll diff = depth%2 == 0 ? target.first - tree[index].pt.first : target.second - tree[index].pt.second;
    int near = diff <= 0 ? tree[index].lc : tree[index].rc;
    int far = diff <= 0 ? tree[index].rc : tree[index].lc;

    nearest(near, depth+1, target, best, bestd);
    if(sqr(diff) < bestd) nearest(far, depth+1, target, best, bestd);
}

int range_min(int index, ll xl, ll xr, ll yl, ll yr) {
    node &t = tree[index];
    if(t.mn == INT_MAX || t.x1 > xr || t.x2 < xl || t.y1 > yr || t.y2 < yl) return INT_MAX;
    if(xl <= t.x1 && t.x2 <= xr && yl <= t.y1 && t.y2 <= yr) return t.mn;
    int res = INT_MAX;
    if(!t.del && xl <= t.pt.first && t.pt.first <= xr && yl <= t.pt.second && t.pt.second <= yr) res = t.id;
    return min({res, range_min(t.lc, xl, xr, yl, yr), range_min(t.rc, xl, xr, yl, yr)});
}

void solve_nearest_queries() {
    int n; cin >> n;
    for(int i=1; i<=n; i++) cin >> p[i].first >> p[i].second;
    iota(ord+1, ord+n+1, 1);
    int root = build(1, n, 0);

    int q; cin >> q;
    while(q--) {
        ll qx, qy; cin >> qx >> qy;
        pll best = {}; ll bestd = LLONG_MAX;
        nearest(root, 0, {qx, qy}, best, bestd);
        cout << best.first << " " << best.second << "\n";
    }
}

void solve_min_id_queries() {
    int n; cin >> n;
    for(int i=1; i<=n; i++) cin >> p[i].first >> p[i].second;
    iota(ord+1, ord+n+1, 1);
    int root = build(1, n, 0);

    int q; cin >> q;
    while(q--) {
        ll xl, xr, yl, yr; cin >> xl >> xr >> yl >> yr;
        int id = range_min(root, xl, xr, yl, yr);
        if(id == INT_MAX) { cout << -1 << "\n"; continue; }
        cout << id << "\n";
        erase_id(id);
    }
}
