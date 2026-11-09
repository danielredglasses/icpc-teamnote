// Gomory-Hu Tree (Gusfield's simplification): the max flow / min cut
// between ANY pair of vertices in the original undirected graph equals
// the minimum edge weight along their path in this tree.
// Time: O(V) max-flow computations -> O(V^3 E) total with the O(V^2 E) Dinic below.
int n;
vi edges[505];
ll capacity[505][505], flow[505][505];
int level[505], idx[505];
int par[505]; ll tree_weight[505];

void add_edge(int u, int v, ll w) {
    if(!capacity[u][v] && !capacity[v][u]) { edges[u].push_back(v); edges[v].push_back(u); }
    capacity[u][v] += w; capacity[v][u] += w;
}

bool find_level(int source, int sink) {
    memset(level, -1, sizeof level);
    queue<int> q; q.push(source);
    level[source] = 0;
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int i : edges[cur]) if(level[i] == -1 && capacity[cur][i] - flow[cur][i] > 0) {
            level[i] = level[cur] + 1;
            q.push(i);
        }
    }
    return level[sink] != -1;
}
ll find_flow(int cur, int sink, ll curflow) {
    if(cur == sink) return curflow;
    for(int &i = idx[cur]; i < edges[cur].size(); i++) {
        int nx = edges[cur][i];
        if(capacity[cur][nx] - flow[cur][nx] > 0 && level[nx] == level[cur] + 1) {
            ll amount = find_flow(nx, sink, min(curflow, capacity[cur][nx] - flow[cur][nx]));
            if(amount > 0) {
                flow[cur][nx] += amount;
                flow[nx][cur] -= amount;
                return amount;
            }
        }
    }
    return 0;
}

ll max_flow(int source, int sink) {
    memset(flow, 0, sizeof flow);
    ll result = 0;
    while(find_level(source, sink)) {
        memset(idx, 0, sizeof idx);
        while(ll amount = find_flow(source, sink, (ll) 4e18)) result += amount;
    }
    return result;
}

void build_gomory_hu() {
    for(int i=2; i<=n; i++) par[i] = 1;
    for(int i=2; i<=n; i++) {
        tree_weight[i] = max_flow(i, par[i]);
        for(int j=i+1; j<=n; j++) if(par[j] == par[i] && level[j] != -1) par[j] = i;
    }
}

ll query(int a, int b) {
    unordered_map<int, ll> seen;
    ll cur = (ll) 4e18;
    int x = a;
    seen[x] = cur;
    while(par[x]) {
        cur = min(cur, tree_weight[x]);
        x = par[x];
        seen[x] = cur;
    }
    cur = (ll) 4e18;
    x = b;
    while(!seen.count(x)) {
        cur = min(cur, tree_weight[x]);
        x = par[x];
    }
    return min(cur, seen[x]);
}

// usage: set n; add_edge(u, v, w) for every undirected edge; build_gomory_hu(); then
// query(a, b) answers the max flow / min cut between a and b in O(depth) each
void SolveProblem() {
    int m, q; cin >> n >> m;
    for(int i=1; i<=m; i++) {
        int u, v; ll w; cin >> u >> v >> w;
        add_edge(u, v, w);
    }

    build_gomory_hu();

    cin >> q;
    for(int i=1; i<=q; i++) {
        int a, b; cin >> a >> b;
        cout << query(a, b) << "\n";
    }
}
