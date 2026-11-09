vector<pld> e;

void init_hull(vector<pll> &hull) {
    int n = hull.size();
    e.assign(n, pld());
    for(int i=0; i<n; i++) e[i] = {(ld) (hull[(i+1)%n].first - hull[i].first), (ld) (hull[(i+1)%n].second - hull[i].second)};
}

int extreme_point(vector<pll> &hull, pld dir) {
    int n = hull.size();
    pld dp{-dir.second, dir.first};
    pld e0 = e[0];
    auto half_rel = [&](pld x) { 
        ld c = e0.first * x.second - e0.second * x.first; 
        if(c > 0) return 0; 
        if(c < 0) return 1; 
        return e0.first * x.first + e0.second * x.second > 0 ? 0 : 1; 
    };
    auto less_rel = [&](pld a, pld b) { 
        int ha = half_rel(a), hb = half_rel(b); 
        if(ha != hb) return ha < hb; 
        return a.first * b.second - a.second * b.first > 0; 
    };

    int l = 0, r = n-1;
    while(l <= r) {
        int mid = (l+r)/2;
        if(!less_rel(dp, e[mid])) l = mid+1;
        else r = mid-1;
    }
    return (r+1)%n;
}

pair<int, ld> closest_to_line(vector<pll> &hull, pll a, pll b) {
    pld d{(ld) (b.first - a.first), (ld) (b.second - a.second)};
    pld normal{-d.second, d.first};
    ld dlen = sqrtl(d.first * d.first + d.second * d.second);
    auto side = [&](pll q) { return d.first * (q.second - a.second) - d.second * (q.first - a.first); };
    int hi = extreme_point(hull, normal), lo = extreme_point(hull, {-normal.first, -normal.second});
    ld s_hi = side(hull[hi]), s_lo = side(hull[lo]);
    if(s_hi >= 0 && s_lo <= 0) return {s_hi == 0 ? hi : lo, 0};
    if(s_lo > 0) return {lo, s_lo / dlen};
    return {hi, -s_hi / dlen};
}
