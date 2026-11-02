pld polygon_centroid(vector<pld> &poly) {
    ld cx = 0, cy = 0, area = 0;
    int n = poly.size();
    for(int i=0; i<n; i++) {
        pld p = poly[i], q = poly[(i+1) % n];
        ld cross = p.first * q.second - q.first * p.second;
        area += cross;
        cx += (p.first + q.first) * cross;
        cy += (p.second + q.second) * cross;
    }
    area /= 2;
    return pld(cx / (6*area), cy / (6*area));
}
