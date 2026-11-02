// Time: O(r^2 n) independence-oracle calls (r = |result|, n = |E|). Finds
// a maximum common independent set of two matroids on ground set
// {0,...,n-1}, given independence oracles indep1/indep2 (each takes a
// candidate subset as a vector<bool> of size n, true iff independent).
vector<int> matroid_intersection(int n, function<bool(vector<bool>&)> indep1, function<bool(vector<bool>&)> indep2) {
    vector<bool> in_set(n, false);
    while(true) {
        vector<int> par(n, -2);
        queue<int> q;
        int sink = -1;
        for(int y=0; y<n && sink==-1; y++) if(!in_set[y]) {
            in_set[y] = true; bool a1 = indep1(in_set); in_set[y] = false;
            if(a1) {
                par[y] = -1;
                q.push(y);
                in_set[y] = true; bool a2 = indep2(in_set); in_set[y] = false;
                if(a2) sink = y;
            }
        }
        while(!q.empty() && sink==-1) {
            int u = q.front(); q.pop();
            for(int v=0; v<n; v++) if(par[v]==-2) {
                bool edge = false;
                if(in_set[u] && !in_set[v]) {
                    in_set[u] = false; in_set[v] = true;
                    edge = indep1(in_set);
                    in_set[u] = true; in_set[v] = false;
                } else if(!in_set[u] && in_set[v]) {
                    in_set[v] = false; in_set[u] = true;
                    edge = indep2(in_set);
                    in_set[v] = true; in_set[u] = false;
                }
                if(edge) {
                    par[v] = u;
                    if(!in_set[v]) {
                        in_set[v] = true; bool a2 = indep2(in_set); in_set[v] = false;
                        if(a2) { sink = v; break; }
                    }
                    q.push(v);
                }
            }
        }
        if(sink==-1) break;
        int cur = sink;
        while(cur != -1) { in_set[cur] = !in_set[cur]; cur = par[cur]; }
    }
    vector<int> result;
    for(int i=0; i<n; i++) if(in_set[i]) result.push_back(i);
    return result;
}
