int circle_line_intersect(pld c, ld r, pld a, pld b, vector<pld> &result) {
    pld d(b.first - a.first, b.second - a.second);
    ld len2 = d.first*d.first + d.second*d.second;
    ld t = ((c.first - a.first) * d.first + (c.second - a.second) * d.second) / len2;
    pld foot(a.first + t * d.first, a.second + t * d.second);
    ld dist2 = (foot.first - c.first) * (foot.first - c.first) + (foot.second - c.second) * (foot.second - c.second);
    ld r2 = r*r;
    if(dist2 > r2 + 1e-9) return 0;

    ld len = sqrtl(len2);
    ld ux = d.first / len, uy = d.second / len;
    if(dist2 >= r2 - 1e-9) { // tangent
        result.push_back(foot);
        return 1; 
    }

    ld h = sqrtl(r2 - dist2);
    result.push_back(pld(foot.first - ux*h, foot.second - uy*h));
    result.push_back(pld(foot.first + ux*h, foot.second + uy*h));
    return 2;
}
