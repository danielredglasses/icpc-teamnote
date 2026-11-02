vector<pld> min_bounding_rectangle(vector<pll> &hull) {
    int n = hull.size();
    auto proj = [&](int idx, ld ux, ld uy) { return hull[idx].first*ux + hull[idx].second*uy; };

    ld ux = hull[1].first - hull[0].first, uy = hull[1].second - hull[0].second;
    ld len0 = hypotl(ux, uy); ux /= len0; uy /= len0;
    ld vx = -uy, vy = ux;
    int pr = 0, pt = 0, pl = 0; // max along +u, max along +v, max along -u
    for(int i=1; i<n; i++) {
        if(proj(i, ux, uy) > proj(pr, ux, uy)) pr = i;
        if(proj(i, vx, vy) > proj(pt, vx, vy)) pt = i;
        if(proj(i, -ux, -uy) > proj(pl, -ux, -uy)) pl = i;
    }

    ld best = -1;
    vector<pld> best_corners;
    for(int i=0; i<n; i++) {
        int j = (i+1) % n;
        ld cu = hull[j].first - hull[i].first, cv = hull[j].second - hull[i].second;
        ld len = hypotl(cu, cv); cu /= len; cv /= len;
        ld nx = -cv, ny = cu; // inward normal of this edge

        while(proj((pr+1)%n, cu, cv) > proj(pr, cu, cv) + 1e-12) pr = (pr+1) % n;
        while(proj((pt+1)%n, nx, ny) > proj(pt, nx, ny) + 1e-12) pt = (pt+1) % n;
        while(proj((pl+1)%n, -cu, -cv) > proj(pl, -cu, -cv) + 1e-12) pl = (pl+1) % n;

        ld minp = proj(pl,cu,cv), maxp = proj(pr,cu,cv);
        // minq is hull[i] itself: edge i is a supporting line there
        ld minq = proj(i,nx,ny), maxq = proj(pt,nx,ny);
        ld area = (maxp - minp) * (maxq - minq);
        if(best < 0 || area < best) {
            best = area;
            auto to_xy = [&](ld p, ld q) { return pld(p*cu - q*cv, p*cv + q*cu); };
            best_corners = { to_xy(minp,minq), to_xy(maxp,minq), to_xy(maxp,maxq), to_xy(minp,maxq) };
        }
    }
    return best_corners;
}
