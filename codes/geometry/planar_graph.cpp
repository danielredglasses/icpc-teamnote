int n, m;
vector<pll> p;
vi edges[2005];
int ord[2005][2005];
bool flag[2005][2005];

pll origin;
bool cmp_angle(int a, int b) {
    pll p1 = p[a-1], p2 = p[b-1];
    bool flag1 = p1 > origin, flag2 = p2 > origin;
    if(flag1 != flag2) return flag1 > flag2;
    ll curccw = ccw(origin, p1, p2);
    if(curccw != 0) return curccw > 0;
    return false;
}

vector<vector<pll>> find_faces() {
    memset(flag, false, sizeof(flag));

    for(int i=1; i<=n; i++) {
        origin = p[i-1];
        sort(all(edges[i]), cmp_angle);
        for(int j=0; j<edges[i].size(); j++) ord[i][edges[i][j]] = j;
    }

    vector<vector<pll>> faces;
    for(int i=1; i<=n; i++) for(int j=0; j<edges[i].size(); j++) if(!flag[i][edges[i][j]]) {
        flag[i][edges[i][j]] = true;

        pll cur = {i, edges[i][j]};
        vector<pll> v; v.push_back(p[i-1]);
        while(true) {
            int sz = (int)edges[cur.second].size();
            int nx_ord = (ord[cur.second][cur.first] - 1 + sz) % sz;
            int nx = edges[cur.second][nx_ord];
            if(flag[cur.second][nx]) break;

            v.push_back(p[cur.second - 1]);
            flag[cur.second][nx] = true;
            cur = {cur.second, nx};
        }
        faces.push_back(v);
    }
    return faces;
}
