vi edges[200005], rev_edges[200005];
vi edges_dominator[200005], order; // order = nodes reachable from s, in DFS postorder
int rpo[200005], idom[200005];
bool visited[200005];

void init(int n) {
    for(int i=1; i<=n; i++) {
        edges[i].clear(); rev_edges[i].clear(); edges_dominator[i].clear();
        visited[i] = false; idom[i] = -1;
    }
}

void dfs_order(int index) {
    visited[index] = true;
    for(int nx : edges[index]) if(!visited[nx]) dfs_order(nx);
    order.push_back(index);
}

int intersect(int a, int b) {
    while(a != b) {
        while(rpo[a] > rpo[b]) a = idom[a];
        while(rpo[b] > rpo[a]) b = idom[b];
    }
    return a;
}

void dominator_tree(int s) {
    order.clear();
    dfs_order(s);
    reverse(all(order));
    for(int i=0; i<(int) order.size(); i++) rpo[order[i]] = i;
    for(int v : order) idom[v] = -1;
    idom[s] = s;

    bool changed = true;
    while(changed) {
        changed = false;
        for(int v : order) if(v != s) {
            int new_idom = -1;
            for(int u : rev_edges[v]) {
                if(idom[u] == -1) continue;
                new_idom = new_idom == -1 ? u : intersect(new_idom, u);
            }
            if(new_idom != -1 && idom[v] != new_idom) { idom[v] = new_idom; changed = true; }
        }
    }
    for(int v : order) if(v != s && idom[v] != -1) edges_dominator[idom[v]].push_back(v);
}
