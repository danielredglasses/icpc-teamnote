struct point {
    ld x, y, z;
    point() { }
    point(ld _x, ld _y, ld _z) : x(_x), y(_y), z(_z) { }
    friend ld dist(point &p1, point &p2) {
        ld dx = p1.x - p2.x, dy = p1.y - p2.y, dz = p1.z - p2.z;
        return sqrt(dx*dx + dy*dy + dz*dz);
    }
};

int n;
point points[10005];
point result;
ld rat = 1;

void find_minimum_enclosing_circle() {
    cin >> n;
    for(int i=1; i<=n; i++) cin >> points[i].x >> points[i].y >> points[i].z;
    
    result = point(0, 0, 0);
    for(int i=1; i<=n; i++) {
        result.x += points[i].x;
        result.y += points[i].y;
        result.z += points[i].z;
    }
    result.x /= n; result.y /= n; result.z /= n;
    
    for(int t=0; t<20000; t++) {
        ld maxdist = 0; int idx = -1;
        for(int i=1; i<=n; i++) {
            if(maxdist < dist(result, points[i])) {
                maxdist = dist(result, points[i]);
                idx = i;
            }
        }
        result.x += (points[idx].x - result.x) * rat;
        result.y += (points[idx].y - result.y) * rat;
        result.z += (points[idx].z - result.z) * rat;
        rat *= 0.999;
    }
    
    ld radius = 0;
    for(int i=1; i<=n; i++) radius = max(radius, dist(result, points[i]));
    cout << radius << "\n";
}