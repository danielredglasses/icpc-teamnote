bool z(ld a) { return fabs(a) <= 1e-8; }

// ax+by <= c 
struct half_plane { 
    ld a, b, c; 
    half_plane() { } 
    half_plane(ld _a, ld _b, ld _c) : a(_a), b(_b), c(_c) { }
    friend bool operator < (const half_plane &h1, const half_plane &h2) { 
        bool flag1 = h1.slope() > pld(0, 0);
        bool flag2 = h2.slope() > pld(0, 0); 
        if(flag1 != flag2) return flag1 > flag2; 
        ld curccw = ccw(pld(0, 0), h1.slope(), h2.slope()); 
        return z(curccw) ? h1.c * hypot(h2.a, h2.b) < h2.c * hypot(h1.a, h1.b) : curccw > 0; 
    } 
    friend pld cross(const half_plane &h1, const half_plane &h2) { 
        ld d = h1.a * h2.b - h2.a * h1.b; 
        ld x = (h1.c * h2.b - h1.b * h2.c) / d;
        ld y = (h1.a * h2.c - h1.c * h2.a) / d; 
        return pld(x, y); 
    } 
    friend bool bad(const half_plane &h1, const half_plane &h2, const half_plane &h3) { 
        if(ccw(pld(0, 0), h1.slope(), h2.slope()) <= 0) return false; 
        pld p1 = cross(h1, h2); 
        return h3.a * p1.first + h3.b * p1.second >= h3.c; 
    } 
    pld slope() const { return pld(a, b); } 
};

vector<half_plane> half_planes;

bool hpi(vector<pld> &points) {
    sort(all(half_planes));
    deque<int> dq; 
    for(int i=0; i<half_planes.size(); i++) { 
        if(!dq.empty() && z(ccw(pld(0, 0), half_planes[dq.back()].slope(), half_planes[i].slope()))) continue; 
        while(dq.size() >= 2) { 
            int second = dq.back(); dq.pop_back(); 
            int first = dq.back(); 
            if(!bad(half_planes[first], half_planes[second], half_planes[i])) { 
                dq.push_back(second); 
                break; 
            } 
        } 
        while(dq.size() >= 2) { 
            int first = dq.front(); dq.pop_front(); 
            int second = dq.front(); 
            if(!bad(half_planes[i], half_planes[first], half_planes[second])) { 
                dq.push_front(first); 
                break; 
            } 
        } 
        dq.push_back(i); 
    } 

    while(dq.size() > 2) { 
        int second = dq.back(); dq.pop_back(); 
        int first = dq.back(); 
        if(!bad(half_planes[first], half_planes[second], half_planes[dq.front()])) { 
            dq.push_back(second); 
            break; 
        } 
    } 
    while(dq.size() > 2) { 
        int first = dq.front(); dq.pop_front(); 
        int second = dq.front(); 
        if(!bad(half_planes[dq.back()], half_planes[first], half_planes[second])) { 
            dq.push_front(first); 
            break; 
        } 
    } 

    vi v; 
    while(!dq.empty()) { 
        int cur = dq.front(); dq.pop_front(); 
        v.push_back(cur); 
    } 
        
    for(int i=0; i<v.size(); i++) { 
        int j = (i+1)%v.size(); 
        if(ccw(pld(0, 0), half_planes[v[i]].slope(), half_planes[v[j]].slope()) <= 1e-8) return false;
        points.push_back(cross(half_planes[v[i]], half_planes[v[j]]));
    } 
    return true; 
}