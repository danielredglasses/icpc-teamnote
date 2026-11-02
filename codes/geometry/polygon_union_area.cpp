// Time: O(N^2), N = total vertex count across all polygons.
ld cross2(pld a, pld b) {
    return a.first * b.second - a.second * b.first;
}
pld operator - (pld a, pld b) { return pld(a.first - b.first, a.second - b.second); }
int sgn(ld x) { return (x > 1e-9) - (x < -1e-9); }
ld rat(pld a, pld b) { return sgn(b.first) ? a.first / b.first : a.second / b.second; }

ld poly_union_area(vector<vector<pld>> &poly) {
    ld ret = 0;
    int np = poly.size();
    for(int i=0; i<np; i++) {
        int ni = poly[i].size();
        for(int v=0; v<ni; v++) {
            pld A = poly[i][v], B = poly[i][(v+1) % ni];
            vector<pair<ld,int>> segs = {{0, 0}, {1, 0}};
            for(int j=0; j<np; j++) if(i != j) {
                int nj = poly[j].size();
                for(int u=0; u<nj; u++) {
                    pld C = poly[j][u], D = poly[j][(u+1) % nj];
                    int sc = sgn(ccw(A, B, C)), sd = sgn(ccw(A, B, D));
                    if(sc != sd) {
                        ld sa = ccw(C, D, A), sb = ccw(C, D, B);
                        if(min(sc,sd) < 0) segs.push_back({sa / (sa-sb), sc > sd ? 1 : -1});
                    } else if(sc == 0 && sd == 0 && j < i) {
                        ld dotv = (B.first - A.first) * (D.first - C.first) + (B.second - A.second) * (D.second - C.second);
                        if(dotv > 0) {
                            segs.push_back({rat(C-A, B-A), 1});
                            segs.push_back({rat(D-A, B-A), -1});
                        }
                    }
                }
            }
            sort(segs.begin(), segs.end());
            for(auto &s : segs) s.first = min(max(s.first, (ld)0), (ld)1);
            ld sum = 0;
            int cnt = segs[0].second;
            for(int k=1; k<(int)segs.size(); k++) {
                if(!cnt) sum += segs[k].first - segs[k-1].first;
                cnt += segs[k].second;
            }
            ret += cross2(A,B) * sum;
        }
    }
    return ret / 2;
}
