// Feasible circulation with lower bounds, on top of Dinic. Time: O(V^2 E)
// usage: set n; add_edge(u, v, lower, upper) for every edge;
// bool ok = feasible_circulation();
// if ok, actual flow on each edge = lower + (upper-lower - remaining .cap
// on that edge's Dinic entry)
// Each edge keeps flow in [lower, upper]; every vertex must conserve flow.
// Flow actually pushed on an edge = lower + (upper - lower - e.cap).
struct edge { 
    int to, rev; 
    ll cap; 
};
int n; // real vertices are 1..n, super source/sink are n+1, n+2
vector<edge> edges[405];
int level[405], idx[405];
ll excess[405];

void add_edge(int u, int v, ll lower, ll upper) {
    edges[u].push_back({v, (int) edges[v].size(), upper - lower});
    edges[v].push_back({u, (int) edges[u].size()-1, 0});
    excess[v] += lower; excess[u] -= lower;
}

bool find_level(int source, int sink) {
    memset(level, -1, sizeof level);
    queue<int> q; q.push(source);
    level[source] = 0;
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(edge &e : edges[cur]) if(level[e.to] == -1 && e.cap > 0) {
            level[e.to] = level[cur] + 1;
            q.push(e.to);
        }
    }
    return level[sink] != -1;
}

ll find_flow(int cur, int sink, ll curflow) {
    if(cur == sink) return curflow;
    for(int &i = idx[cur]; i < edges[cur].size(); i++) {
        edge &e = edges[cur][i];
        if(e.cap > 0 && level[e.to] == level[cur] + 1) {
            ll amount = find_flow(e.to, sink, min(curflow, e.cap));
            if(amount > 0) {
                e.cap -= amount;
                edges[e.to][e.rev].cap += amount;
                return amount;
            }
        }
    }
    return 0;
}

ll max_flow(int source, int sink) {
    ll result = 0;
    while(find_level(source, sink)) {
        memset(idx, 0, sizeof idx);
        while(ll amount = find_flow(source, sink, 4e18)) result += amount;
    }
    return result;
}

bool feasible_circulation() {
    int ss = n+1, tt = n+2;
    ll need = 0;
    for(int i=1; i<=n; i++) {
        if(excess[i] > 0) { add_edge(ss, i, 0, excess[i]); need += excess[i]; }
        else if(excess[i] < 0) add_edge(i, tt, 0, -excess[i]);
    }
    return max_flow(ss, tt) == need;
}

// Max s-t flow with lower bounds:
//   add_edge(t, s, 0, 4e18) as the last edge, then feasible_circulation();
//   the flow on that edge is a feasible s-t flow, and max_flow(s, t) on the
//   leftover residual graph increases it to the maximum.
// Min s-t flow: use max_flow(t, s) on the residual instead.

// Example usage: max flow from s to t where each edge has a lower and upper bound.
void SolveProblem() {
    int m, s, t; cin >> n >> m >> s >> t;
    for(int i=1; i<=m; i++) {
        int u, v; ll lower, upper; cin >> u >> v >> lower >> upper;
        add_edge(u, v, lower, upper);
    }

    const ll INF = 4e18;
    int back_idx = edges[t].size();
    // any feasible circulation now carries a feasible s-t flow on this edge
    add_edge(t, s, 0, INF);

    if(!feasible_circulation()) { 
        cout << "infeasible\n"; 
        return; 
    }

    // push more flow on whatever residual capacity is left; this can shuffle
    // flow off of the back edge, so read it after
    ll extra = max_flow(s, t);
    // total flow now sitting on the back edge
    ll base_flow = INF - edges[t][back_idx].cap;

    cout << base_flow + extra << "\n";
}
