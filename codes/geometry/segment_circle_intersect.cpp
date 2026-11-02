int segment_circle_intersect(pld c, ld r, pld a, pld b, vector<pld> &result) {
    vector<pld> line_pts;
    circle_line_intersect(c, r, a, b, line_pts);
    ld dx = b.first - a.first, dy = b.second - a.second, len2 = dx*dx + dy*dy;
    for(auto &p : line_pts) {
        ld t = ((p.first - a.first) * dx + (p.second - a.second) * dy) / len2;
        if(t >= -1e-9 && t <= 1+1e-9) result.push_back(p);
    }
    return result.size();
}
