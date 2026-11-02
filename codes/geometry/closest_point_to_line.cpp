// Time: O(log n). hull must be convex, CCW order, size >= 1.
// index of the hull vertex maximizing dot(v, dir)
int extreme_point(vector<pll> &hull, pld dir) {
    int n = hull.size();
    pld dp{-dir.second, dir.first}; // dir rotated 90 deg CCW
    vector<pld> e(n);
    for(int i=0; i<n; i++) e[i] = {(ld)(hull[(i+1)%n].first - hull[i].first), (ld)(hull[(i+1)%n].second - hull[i].second)};
    pld e0 = e[0];
    auto half_rel = [&](pld x) { ld c = e0.first * x.second - e0.second * x.first; if(c > 0) return 0; if(c < 0) return 1; return e0.first * x.first + e0.second * x.second > 0 ? 0 : 1; };
    auto less_rel = [&](pld a, pld b) { int ha = half_rel(a), hb = half_rel(b); if(ha != hb) return ha < hb; return a.first * b.second - a.second * b.first > 0; };
    
    int l = 0, r = n-1;
    while(l <= r) {
        int mid = (l+r)/2;
        if(!less_rel(dp, e[mid])) l = mid+1;
        else r = mid-1;
    }
    return (r+1)%n;
}


pair<int, ld> closest_to_line(vector<pll> &hull, pll a, pll b) {
    pld d{(ld)(b.first - a.first), (ld)(b.second - a.second)};
    pld normal{-d.second, d.first};
    ld dlen = sqrtl(d.first * d.first + d.second * d.second);
    auto side = [&](pll q) { return d.first * (q.second - a.second) - d.second * (q.first - a.first); };
    ld s0 = side(hull[0]);
    pld dir = s0 >= 0 ? pld{-normal.first, -normal.second} : normal;
    int idx = extreme_point(hull, dir);
    return {idx, fabsl(side(hull[idx])) / dlen};
}
