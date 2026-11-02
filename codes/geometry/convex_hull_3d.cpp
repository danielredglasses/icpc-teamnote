// 3D convex hull via the incremental algorithm. Time: O(n^2).
struct point3 { ld x, y, z; };
point3 operator - (point3 a, point3 b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
point3 cross3(point3 a, point3 b) { return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y*b.x}; }
ld dot3(point3 a, point3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

int n;
point3 p[505];
struct face3 { int a, b, c; };

ld vol6(point3 a, point3 b, point3 c, point3 d) {
    return dot3(cross3(b-a, c-a), d-a);
}

face3 make_face(int a, int b, int c, int inside_pt) {
    if(vol6(p[a], p[b], p[c], p[inside_pt]) > 0) return {a, c, b};
    return {a, b, c};
}

// usage: fill p[0..n-1] and set n (n >= 4); vector<face3> hull = convex_hull_3d();
vector<face3> convex_hull_3d() {
    int i0 = 0, i1 = 1;
    while(i1 < n && dot3(p[i1]-p[i0], p[i1]-p[i0]) < 1e-18) i1++;
    int i2 = i1+1;
    while(i2 < n) {
        point3 cr = cross3(p[i1]-p[i0], p[i2]-p[i0]);
        if(dot3(cr, cr) > 1e-18) break;
        i2++;
    }
    int i3 = i2+1;
    while(i3 < n && fabsl(vol6(p[i0], p[i1], p[i2], p[i3])) < 1e-9) i3++;
    if(i1 >= n || i2 >= n || i3 >= n) return {};

    vector<face3> faces;
    faces.push_back(make_face(i0, i1, i2, i3));
    faces.push_back(make_face(i0, i1, i3, i2));
    faces.push_back(make_face(i0, i2, i3, i1));
    faces.push_back(make_face(i1, i2, i3, i0));

    for(int t=0; t<n; t++) {
        if(t == i0 || t == i1 || t == i2 || t == i3) continue;

        vector<bool> vis(faces.size());
        bool any = false;
        for(int i=0; i<faces.size(); i++) {
            vis[i] = vol6(p[faces[i].a], p[faces[i].b], p[faces[i].c], p[t]) > 1e-9;
            any = any || vis[i];
        }
        if(!any) continue; 

        map<pii, int> owner;
        for(int i=0; i<faces.size(); i++) {
            owner[{faces[i].a, faces[i].b}] = i;
            owner[{faces[i].b, faces[i].c}] = i;
            owner[{faces[i].c, faces[i].a}] = i;
        }

        vector<face3> added;
        for(int i=0; i<faces.size(); i++) if(vis[i]) {
            int e[3][2] = {{faces[i].a, faces[i].b}, {faces[i].b, faces[i].c}, {faces[i].c, faces[i].a}};
            for(auto &ed : e) {
                int u = ed[0], v = ed[1];
                auto it = owner.find({v, u});
                if(it == owner.end() || !vis[it->second]) added.push_back({u, v, t});
            }
        }

        vector<face3> kept;
        for(int i=0; i<faces.size(); i++) if(!vis[i]) kept.push_back(faces[i]);
        for(auto &f : added) kept.push_back(f);
        faces = kept;
    }
    return faces;
}
