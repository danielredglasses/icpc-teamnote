// a segment endpoint plus the bookkeeping the sweep needs, NOT just a plain point
struct sweep_event {
    pll p; bool isend; int idx;
    sweep_event() { }
    sweep_event(pll _p, bool _isend, int _idx) : p(_p), isend(_isend), idx(_idx) { }
    friend bool operator < (const sweep_event &e1, const sweep_event &e2) {
        return make_pair(make_pair(e1.p.first, e1.isend), make_pair(e1.p.second, e1.idx)) < make_pair(make_pair(e2.p.first, e2.isend), make_pair(e2.p.second, e2.idx));
    }
};

ll curx;
struct line {
    pll p1, p2;
    pll slope; ll c;
    int idx = -1;
    line() { }
    line(pll _p1, pll _p2) {
        if(_p1 > _p2) swap(_p1, _p2);
        p1 = _p1; p2 = _p2;
        slope = make_pair(p2.first - p1.first, p2.second - p1.second);
        c = slope.first * p1.second - slope.second * p1.first;
    }
    friend bool operator < (const line &l1, const line &l2) {
        bool vert1 = l1.p1.first == l1.p2.first, vert2 = l2.p1.first == l2.p2.first;
        ld y1 = vert1 ? l1.p1.second : (ld) (l1.slope.second * curx + l1.c) / l1.slope.first;
        ld y2 = vert2 ? l2.p1.second : (ld) (l2.slope.second * curx + l2.c) / l2.slope.first;
        if(y1 != y2) return y1 < y2;

        // tie at the sweep x: break by slope so order matches segments'
        // position just past curx
        if(vert1 != vert2) return vert2; // vertical = steepest
        if(!vert1 && !vert2) {
            ll cross = l1.slope.second * l2.slope.first - l2.slope.second * l1.slope.first;
            if(cross != 0) return cross < 0;
        }
        return l1.idx < l2.idx;
    }
};

bool on_segment(pll p, pll a, pll b) {
    if(a > b) swap(a, b);
    return a <= p && p <= b;
}

// count_touching=true: any shared point counts (endpoint touching another
// segment, shared endpoints, collinear overlap)
// count_touching=false: only a genuine transversal crossing through both
// segments' interiors counts
bool isintersect(const line &l1, const line &l2, bool count_touching = true) {
    pll p1 = l1.p1, p2 = l1.p2, p3 = l2.p1, p4 = l2.p2;
    // a degenerate (zero-length) segment can only touch, never properly cross
    if(p1 == p2 || p3 == p4) {
        if(!count_touching) return false;
        if(p1 == p2 && p3 == p4) return p1 == p3;
        if(p1 == p2) return ccw(p3, p4, p1) == 0 && on_segment(p1, p3, p4);
        return ccw(p1, p2, p3) == 0 && on_segment(p3, p1, p2);
    }
    ll ccw1 = ccw(p1, p2, p3), ccw2 = ccw(p1, p2, p4), ccw3 = ccw(p3, p4, p1), ccw4 = ccw(p3, p4, p2);
    if(ccw1 == 0 && ccw2 == 0) { // collinear
        if(!count_touching) return false;
        if(p2 < p3 || p4 < p1) return false;
        return true;
    }
    if((ccw1 > 0 && ccw2 > 0) || (ccw1 < 0 && ccw2 < 0)) return false;
    if((ccw3 > 0 && ccw4 > 0) || (ccw3 < 0 && ccw4 < 0)) return false;
    if(!count_touching && (ccw1 == 0 || ccw2 == 0 || ccw3 == 0 || ccw4 == 0)) return false;
    return true;
}
int n;
vector<line> lines;
vector<sweep_event> events;
multiset<line> curlines;
unordered_map<int, multiset<line>::iterator> where;

bool shamos_hoey(bool count_touching, pii &ans) {
    n = lines.size();
    events.clear(); curlines.clear(); where.clear();
    for(int i=0; i<n; i++) {
        lines[i].idx = i;
        events.push_back(sweep_event(lines[i].p1, false, i));
        events.push_back(sweep_event(lines[i].p2, true, i));
    }
    sort(all(events));

    for(int i=0; i<n*2; i++) {
        curx = events[i].p.first;
        int idx = events[i].idx;
        if(!events[i].isend) {
            auto it = where[idx] = curlines.insert(lines[idx]);
            if(it != curlines.begin() && isintersect(*prev(it), *it, count_touching)) { 
                ans = {prev(it)->idx, it->idx}; 
                return true; 
            }
            if(next(it) != curlines.end() && isintersect(*it, *next(it), count_touching)) {
                ans = {it->idx, next(it)->idx}; 
                return true; 
            }
        }
        else {
            auto it = where[idx];
            bool has_prev = it != curlines.begin(), has_next = next(it) != curlines.end();
            auto pr = has_prev ? prev(it) : it, nx = next(it);
            curlines.erase(it);
            if(has_prev && has_next && isintersect(*pr, *nx, count_touching)) { 
                ans = {pr->idx, nx->idx}; 
                return true; 
            }
        }
    }
    return false;
}
