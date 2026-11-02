// Time: iterative dominance computation, O(V+E) per pass; converges in a
// small constant number of passes for typical CFGs (handles cycles, unlike
// a plain topological sweep)
vector<pll> edges[200005], rev_edges[200005];
vi edges_dominator[200005], order; // order = nodes reachable from s, in DFS postorder
// rpo = reverse-postorder number (smaller = closer to s)
int rpo[200005], idom[200005];
bool visited[200005];

void dfs_order(int index) {
    visited[index] = true;
    for(pll e : edges[index]) if(!visited[e.first]) dfs_order(e.first);
    order.push_back(index);
}

// walk two idom-chain candidates up to their common ancestor, using rpo
// to decide which side climbs
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
            for(pll e : rev_edges[v]) {
                if(idom[e.first] == -1) continue;
                new_idom = (new_idom == -1) ? e.first : intersect(new_idom, e.first);
            }
            if(new_idom != -1 && idom[v] != new_idom) { idom[v] = new_idom; changed = true; }
        }
    }
    for(int v : order) if(v != s && idom[v] != -1) edges_dominator[idom[v]].push_back(v);
}
