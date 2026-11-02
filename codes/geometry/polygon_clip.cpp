vector<pld> cut_polygon(const vector<pld> &poly, pld s, pld e) {
    vector<pld> res;
    int n = poly.size();
    for(int i=0; i<n; i++) {
        pld cur = poly[i], prv = i ? poly[i-1] : poly.back();
        ld a = ccw(s, e, cur), b = ccw(s, e, prv);
        if((a < 0) != (b < 0)) {
            ld t = a / (a - b);
            res.push_back(pld(cur.first + (prv.first - cur.first) * t, cur.second + (prv.second - cur.second) * t));
        }
        if(a >= 0) res.push_back(cur);
    }
    return res;
}
