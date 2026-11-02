// Time: expected O(n) (randomized incremental, thanks to shuffling the input order)
struct circle {
    pld c; ld r;
    circle() { }
    circle(pld _c, ld _r) : c(_c), r(_r) { }
    friend bool operator < (const circle &c1, const circle &c2) { return c1.r < c2.r; }
};

ld mag(pld p) { return p.first * p.first + p.second * p.second; }
ld dist(pld p1, pld p2) {
    ld dx = p2.first - p1.first, dy = p2.second - p1.second;
    return hypot(dx, dy);
}
pld center(pld p1, pld p2, pld p3) {
    ld cx = -((mag(p2) - mag(p1)) * (p3.second - p2.second) - (mag(p2) - mag(p3)) * (p1.second - p2.second)) / (2*(p1.first - p2.first) * (p3.second - p2.second) - 2*(p3.first - p2.first) * (p1.second - p2.second));
    ld cy = -((mag(p2) - mag(p1)) * (p3.first - p2.first) - (mag(p2) - mag(p3)) * (p1.first - p2.first)) / (2*(p1.second - p2.second) * (p3.first - p2.first) - 2*(p3.second - p2.second) * (p1.first - p2.first));
    return pld(cx, cy);
}
pld center(pld p1, pld p2) {
    return pld((p1.first + p2.first) / 2, (p1.second + p2.second) / 2);
}

circle mec3(pld p1, pld p2, pld p3) {
    pld c01 = center(p1, p2); ld r01 = dist(c01, p1);
    if(dist(c01, p3) <= r01 + 1e-9) return circle(c01, r01);
    pld c02 = center(p1, p3); ld r02 = dist(c02, p1);
    if(dist(c02, p2) <= r02 + 1e-9) return circle(c02, r02);
    pld c12 = center(p2, p3); ld r12 = dist(c12, p2);
    if(dist(c12, p1) <= r12 + 1e-9) return circle(c12, r12);
    pld c = center(p1, p2, p3);
    return circle(c, dist(c, p1));
}

int n;
pld points[1005];

void find_minimum_enclosing_circle() {
    cin >> n;
    for(int i=1; i<=n; i++) cin >> points[i].first >> points[i].second;
    random_device rd;
    mt19937 gen(rd());
    shuffle(points+1, points+n+1, gen);
    
    circle result(pld(0, 0), 0);
    for(int i=1; i<=n; i++) if(dist(result.c, points[i]) > result.r) {
        result.c = points[i];
        result.r = 0;
        for(int j=1; j<i; j++) if(dist(result.c, points[j]) > result.r) {
            result.c = center(points[i], points[j]);
            result.r = dist(result.c, points[j]);
            for(int k=1; k<j; k++) if(dist(result.c, points[k]) > result.r) {
                result = mec3(points[i], points[j], points[k]);
            }
        }
    }

    cout << result.c.first << " " << result.c.second << "\n";
    cout << result.r << "\n";
}
