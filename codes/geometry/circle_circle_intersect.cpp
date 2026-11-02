int circle_circle_intersect(pld c1, ld r1, pld c2, ld r2, vector<pld> &result) {
    ld dx = c2.first - c1.first, dy = c2.second - c1.second;
    ld d2 = dx*dx + dy*dy, d = sqrtl(d2);
    if(d < 1e-12) return (fabsl(r1-r2) < 1e-9) ? -1 : 0; // same center
    if(d > r1+r2 + 1e-9 || d < fabsl(r1-r2) - 1e-9) return 0;

    ld a = (d2 + r1*r1 - r2*r2) / (d*2);
    ld h2 = r1*r1 - a*a;
    pld foot(c1.first + a*dx/d, c1.second + a*dy/d);
    if(h2 < 1e-9) { 
        result.push_back(foot); 
        return 1; 
    }

    ld h = sqrtl(max((ld)0, h2));
    ld ux = -dy / d, uy = dx / d;
    result.push_back(pld(foot.first - ux*h, foot.second - uy*h));
    result.push_back(pld(foot.first + ux*h, foot.second + uy*h));
    return 2;
}
