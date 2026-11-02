bool on_segment(pll p, pll a, pll b) {
    if(a > b) swap(a, b);
    return a <= p && p <= b;
}

// Returns 1 if q is strictly inside, 0 if on the boundary, -1 if outside.
int point_in_convex(vector<pll> &poly, pll q) {
    int n = poly.size();
    ll c1 = ccw(poly[0], poly[1], q), c2 = ccw(poly[0], poly[n-1], q);
    if(c1 < 0 || c2 > 0) return -1;
    if(c1 == 0) return on_segment(q, poly[0], poly[1]) ? 0 : -1;
    if(c2 == 0) return on_segment(q, poly[0], poly[n-1]) ? 0 : -1;

    int l = 1, r = n-2;
    while(l <= r) {
        int mid = (l+r)/2;
        if(ccw(poly[0], poly[mid], q) >= 0) l = mid+1; 
        else r = mid-1;
    }
    int lo = r, hi = r+1;
    ll c = ccw(poly[lo], poly[hi], q);
    if(c > 0) return 1;
    if(c == 0) return 0;
    return -1;
}

// Returns 1 if q is strictly inside, 0 if on the boundary, -1 if outside.
int point_in_polygon(vector<pll> &poly, pll q) {
    int n = poly.size();
    bool inside = false;
    for(int i=0; i<n; i++) {
        pll a = poly[i], b = poly[(i+1)%n];
        if(ccw(a, b, q) == 0 && on_segment(q, a, b)) return 0;
        if((a.second > q.second) != (b.second > q.second)) {
            ll cross = (b.first - a.first) * (q.second - a.second) - (q.first - a.first) * (b.second - a.second);
            if((cross > 0) == (b.second > a.second)) inside = !inside;
        }
    }
    return inside ? 1 : -1;
}
