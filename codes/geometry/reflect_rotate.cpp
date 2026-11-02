// reflect point p across point c (point symmetry)
pld reflect_point(pld p, pld c) { return pld(c.first * 2 - p.first, c.second * 2 - p.second); }

// reflect point p across the line through a,b (a != b)
pld reflect_line(pld p, pld a, pld b) {
    pld d(b.first - a.first, b.second - a.second);
    ld t = ((p.first - a.first) * d.first + (p.second - a.second) * d.second) / (d.first * d.first + d.second * d.second);
    pld foot(a.first + t * d.first, a.second + t * d.second);
    return reflect_point(p, foot);
}

// rotate point p by angle theta (radians, CCW) around center c
pld rotate_point(pld p, pld c, ld theta) {
    ld dx = p.first - c.first, dy = p.second - c.second;
    ld cosT = cosl(theta), sinT = sinl(theta);
    return pld(c.first + dx * cosT - dy * sinT, c.second + dx * sinT + dy * cosT);
}

// usage: apply the point functions above to both endpoints for a segment
pair<pld, pld> reflect_segment_point(pair<pld, pld> seg, pld c) {
    return {reflect_point(seg.first, c), reflect_point(seg.second, c)};
}
pair<pld, pld> reflect_segment_line(pair<pld, pld> seg, pld a, pld b) {
    return {reflect_line(seg.first, a, b), reflect_line(seg.second, a, b)};
}
pair<pld, pld> rotate_segment(pair<pld, pld> seg, pld c, ld theta) {
    return {rotate_point(seg.first, c, theta), rotate_point(seg.second, c, theta)};
}
