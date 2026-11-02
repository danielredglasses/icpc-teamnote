/*
Time: O(n log n)
input: order will be changed, sorted by (y,x) order
vertex: voronoi intersection points, degree 3, may duplicated
edge: may contain inf line (-1)
area
  - (a,b) = i-th element of area
  - (u,v) = i-th element of edge
  - input[a] is located CCW of u->v line
  - input[b] is located CW of u->v line
  - u->v line is a subset of perpendicular bisector of input[a] to input[b] segment
  - Straight line {a, b}, {-1, -1} through midpoint of input[a] and input[b]
*/

#define x first
#define y second

ld operator / (pld a, pld b){ return a.first * b.second - a.second * b.first; }
pld operator * (ld b, pld a){ return pld(b * a.first, b * a.second); }
pld operator + (pld a, pld b){ return pld(a.first + b.first, a.second + b.second); }
pld operator - (pld a, pld b){ return pld(a.first - b.first, a.second - b.second); }

const ld EPS = 1e-9;
int dcmp(ld x) { return x < -EPS ? -1 : x > EPS ? 1 : 0; }
// sq(x) = x*x, size(p) = hypot(p.x, p.y)
// sz2(p) = sq(p.x)+sq(p.y), r90(p) = (-p.y, p.x)
ld sq(ld x) { return x * x; }
ld size(pld p) { return hypot(p.x, p.y); }
ld sz2(pld p) { return sq(p.x) + sq(p.y); }
pld r90(pld p) { return pld(-p.y, p.x); }
pld line_intersect(pld a, pld b, pld u, pld v) { return u + (((a - u) / b) / (v / b)) * v; }
pld get_circumcenter(pld p0, pld p1, pld p2) {
    return line_intersect(0.5 * (p0 + p1), r90(p0 - p1), 0.5 * (p1 + p2), r90(p1 - p2));
}
ld pb_int(pld left, pld right, ld sweepline) {
    if (dcmp(left.y - right.y) == 0)
        return (left.x + right.x) / 2.0;
    int sign = left.y < right.y ? -1 : 1;
    pld v = line_intersect(left, right - left, pld(0, sweepline), pld(1, 0));
    ld d1 = sz2(0.5 * (left + right) - v), d2 = sz2(0.5 * (left - right));
    return v.x + sign * sqrt(std::max((ld) 0.0, d1 - d2));
}

struct bnode {
    pld point;
    int idx, end;
    int link[2], par, prv, nxt; // 0 = null
};

bnode nodes[400005]; int node_cnt = 0; // size = 4 * (number of points)

int new_node(pld point, int idx) {
    int cur = ++node_cnt;
    nodes[cur] = {point, idx, 0, {0, 0}, 0, 0, 0};
    return cur;
}

struct Beachline {
    int root = 0;
    ld sweepline = -1e20;

    inline int dir(int n) { return nodes[nodes[n].par].link[0] != n; }
    void rotate(int n) {
        int p = nodes[n].par, d = dir(n);
        nodes[p].link[d] = nodes[n].link[!d];
        if (nodes[n].link[!d]) nodes[nodes[n].link[!d]].par = p;
        nodes[n].par = nodes[p].par;
        if (nodes[p].par) nodes[nodes[p].par].link[dir(p)] = n;
        nodes[n].link[!d] = p;
        nodes[p].par = n;
    }
    void splay(int x, int f = 0) {
        while (nodes[x].par != f) {
            if (nodes[nodes[x].par].par == f);
            else if (dir(x) == dir(nodes[x].par)) rotate(nodes[x].par);
            else rotate(x);
            rotate(x);
        }
        if (!f) root = x;
    }
    void insert(int n, int p, int d) {
        splay(p);
        int c = nodes[p].link[d];
        nodes[n].link[d] = c;
        if (c) nodes[c].par = n;
        nodes[p].link[d] = n;
        nodes[n].par = p;
        int prv = !d ? nodes[p].prv : p, nxt = !d ? p : nodes[p].nxt;
        nodes[n].prv = prv;
        if (prv) nodes[prv].nxt = n;
        nodes[n].nxt = nxt;
        if (nxt) nodes[nxt].prv = n;
    }
    void erase(int n) {
        int prv = nodes[n].prv, nxt = nodes[n].nxt;
        if (!prv && !nxt) {
            if (n == root) root = 0;
            return;
        }
        nodes[n].prv = 0;
        if (prv) nodes[prv].nxt = nxt;
        nodes[n].nxt = 0;
        if (nxt) nodes[nxt].prv = prv;
        splay(n);
        if (!nxt) {
            nodes[root].par = 0;
            nodes[n].link[0] = 0;
            root = prv;
        }
        else {
            splay(nxt, n);
            int c = nodes[n].link[0];
            nodes[nxt].link[0] = c;
            nodes[c].par = nxt;
            nodes[n].link[0] = 0;
            nodes[n].link[1] = 0;
            nodes[nxt].par = 0;
            root = nxt;
        }
    }
    bool get_event(int cur, ld &next_sweep) {
        if (!nodes[cur].prv || !nodes[cur].nxt) return false;
        pld u = r90(nodes[cur].point - nodes[nodes[cur].prv].point);
        pld v = r90(nodes[nodes[cur].nxt].point - nodes[cur].point);
        if (dcmp(u / v) != 1) return false;
        pld p = get_circumcenter(nodes[cur].point, nodes[nodes[cur].prv].point, nodes[nodes[cur].nxt].point);
        next_sweep = p.y + size(p - nodes[cur].point);
        return true;
    }
    int find_bl(ld x) {
        int cur = root;
        while (cur) {
            ld left = nodes[cur].prv ? pb_int(nodes[nodes[cur].prv].point, nodes[cur].point, sweepline) : -1e30;
            ld right = nodes[cur].nxt ? pb_int(nodes[cur].point, nodes[nodes[cur].nxt].point, sweepline) : 1e30;
            if (left <= x && x <= right) {
                splay(cur);
                return cur;
            }
            cur = nodes[cur].link[x > right];
        }
        return 0;
    }
};

struct event {
    int type, idx, prv, nxt, cur;
    ld sweep;
    event(ld sweep, int idx) : type(0), idx(idx), prv(0), nxt(0), cur(0), sweep(sweep) { }
    event(ld sweep, int cur, bool circle) : type(1), idx(0), prv(nodes[nodes[cur].prv].idx), nxt(nodes[nodes[cur].nxt].idx), cur(cur), sweep(sweep) { }
    bool operator>(const event &l) const { return sweep > l.sweep; }
};

void VoronoiDiagram(vector<pld> &input, vector<pld> &vertex, vector<pii> &edge, vector<pii> &area) {
    Beachline bl = Beachline();
    priority_queue<event, vector<event>, greater<event>> events;
    auto add_edge = [&](int u, int v, int a, int b, int c1, int c2) {
        if (c1) nodes[c1].end = edge.size() * 2;
        if (c2) nodes[c2].end = edge.size() * 2 + 1;
        edge.emplace_back(u, v);
        area.emplace_back(a, b);
    };
    auto write_edge = [&](int idx, int v){
        idx % 2 == 0 ? edge[idx / 2].x = v : edge[idx / 2].y = v;
    };
    auto add_event = [&](int cur) {
        ld nxt;
        if(bl.get_event(cur, nxt)) events.emplace(nxt, cur, true);
    };
    int n = input.size(), cnt = 0;
    node_cnt = 0;
    sort(all(input), [] (const pld &l, const pld &r) {
        return l.y != r.y ? l.y < r.y : l.x < r.x;
    });
    int tmp = bl.root = new_node(input[0], 0), t2;
    for (int i = 1; i < n; i++) {
        if (dcmp(input[i].y - input[0].y) == 0) {
            add_edge(-1, -1, i - 1, i, 0, tmp);
            bl.insert(t2 = new_node(input[i], i), tmp, 1);
            tmp = t2;
        }
        else events.emplace(input[i].y, i);
    }
    while (events.size()) {
        event q = events.top();
        events.pop();
        int prv, cur, nxt, site;
        int v = vertex.size(), idx = q.idx;
        bl.sweepline = q.sweep;
        if (q.type == 0) {
            pld point = input[idx];
            cur = bl.find_bl(point.x);
            bl.insert(site = new_node(point, idx), cur, 0);
            bl.insert(prv = new_node(nodes[cur].point, nodes[cur].idx), site, 0);
            add_edge(-1, -1, nodes[cur].idx, idx, site, prv);
            add_event(prv);
            add_event(cur);
        }
        else {
            cur = q.cur, prv = nodes[cur].prv, nxt = nodes[cur].nxt;
            if (!prv || !nxt || nodes[prv].idx != q.prv || nodes[nxt].idx != q.nxt) continue;
            vertex.push_back(get_circumcenter(nodes[prv].point, nodes[nxt].point, nodes[cur].point));
            write_edge(nodes[prv].end, v);
            write_edge(nodes[cur].end, v);
            add_edge(v, -1, nodes[prv].idx, nodes[nxt].idx, 0, prv);
            bl.erase(cur);
            add_event(prv);
            add_event(nxt);
        }
    }
}
