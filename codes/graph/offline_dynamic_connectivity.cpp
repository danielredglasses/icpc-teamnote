int n, m = 0, q;
pii edges[100005]; int in[100005] = {0}, out[100005] = {0};
pii queries[100005]; int query_cnt = 0;

int result[100005] = {0};

vi nodes[400005];
void update(int index, int l, int r, int s, int e, int edge_idx) {
    if(r < s || l > e) return;
    if(s <= l && r <= e) {
        nodes[index].push_back(edge_idx);
        return;
    }
    int mid = (l+r)/2;
    update(index*2, l, mid, s, e, edge_idx); update(index*2+1, mid+1, r, s, e, edge_idx);
}

int group[100005];
int find_group(int index) {
    return group[index] == index ? index : find_group(group[index]);    
}

stack<int> st;
int sz[100005] = {0};
void Union(int a, int b) {
    if(sz[a] < sz[b]) swap(a, b);
    group[b] = a; sz[a] += sz[b];
    st.push(b);
}

void go_back(int x) {
    while(x--) {
        int a = st.top(); st.pop();
        sz[group[a]] -= sz[a]; group[a] = a;
    }
}

void divide(int index, int l, int r) {
    int cnt = 0;
    for(int edge_idx : nodes[index]) {
        int g1 = find_group(edges[edge_idx].first), g2 = find_group(edges[edge_idx].second);
        if(g1 != g2) {
            Union(g1, g2);
            cnt++;
        }
    }
    
    if(l == r) {
        int g1 = find_group(queries[l].first), g2 = find_group(queries[l].second);
        result[l] = g1 == g2;
        go_back(cnt);
        return;
    }
    
    int mid = (l+r)/2;
    divide(index*2, l, mid); divide(index*2+1, mid+1, r);
    go_back(cnt);
}

void SolveProblem() {
    cin >> n >> q;
    
    map<pii, int> idx;
    for(int i=1; i<=q; i++) {
        int type, a, b; cin >> type >> a >> b;
        if(a > b) swap(a, b);
        if(type == 1) {
            edges[++m] = {a, b};
            in[m] = query_cnt+1; out[m] = -1;
            idx[{a, b}] = m;
        }
        else if(type == 2) {
            int cur_idx = idx[{a, b}];
            out[cur_idx] = query_cnt;
        }
        else queries[++query_cnt] = {a, b};
    }
    for(int i=1; i<=m; i++) if(out[i] == -1) out[i] = query_cnt;
        
    for(int i=1; i<=m; i++) if(in[i] <= out[i]) update(1, 1, query_cnt, in[i], out[i], i);
    
    for(int i=1; i<=n; i++) { 
        group[i] = i; 
        sz[i] = 1; 
    }
    divide(1, 1, query_cnt);
    
    for(int i=1; i<=query_cnt; i++) cout << result[i] << "\n";
}