bool cmp_y(pll a, pll b) {
    if(a.second != b.second) return a.second < b.second;
    return a.first < b.first;
}

pll p0;
bool cmp_ccw(pll a, pll b) {
    ll curccw = ccw(p0, a, b);
    if(curccw != 0) return curccw > 0;
    else if(a.second != b.second) return a.second < b.second;
    else return a.first < b.first;
}

vector<pll> create_convex_hull() {
    sort(p+1, p+n+1, cmp_y);

    p0 = p[1];
    sort(p+2, p+n+1, cmp_ccw);

    vector<pll> convex;
    for(int i=1; i<=n; i++) {
        while(convex.size() >= 2) {
            pll second = convex.back(); convex.pop_back();
            pll first = convex.back();
            if(ccw(first, second, p[i]) > 0) {
                convex.push_back(second);
                break;
            }
        }
        convex.push_back(p[i]);
    }
    return convex;
}