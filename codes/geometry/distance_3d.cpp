struct point3 { ld x, y, z; };
point3 operator-(point3 a, point3 b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
point3 cross3(point3 a, point3 b) { return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x}; }
ld dot3(point3 a, point3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
ld norm3(point3 a) { return sqrtl(dot3(a, a)); }

// distance from point p to the line through a with direction d
ld point_line_dist_3d(point3 p, point3 a, point3 d) {
    return norm3(cross3(p - a, d)) / norm3(d);
}

// distance between line (a1, dir d1) and line (a2, dir d2);
// handles skew, intersecting, and parallel lines
ld line_line_dist_3d(point3 a1, point3 d1, point3 a2, point3 d2) {
    point3 n = cross3(d1, d2);
    ld nn = norm3(n);
    // parallel (or identical) lines
    if(nn < 1e-9) return point_line_dist_3d(a2, a1, d1);
    return fabsl(dot3(a2-a1, n)) / nn; // skew or intersecting (0 if intersecting)
}

// distance from point p to the plane through a with normal n
ld point_plane_dist_3d(point3 p, point3 a, point3 n) {
    return fabsl(dot3(p-a, n)) / norm3(n);
}
// distance from point p to the plane through a, b, c
ld point_plane_dist_3d(point3 p, point3 a, point3 b, point3 c) {
    return point_plane_dist_3d(p, a, cross3(b-a, c-a));
}
