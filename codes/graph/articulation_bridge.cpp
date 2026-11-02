int nodenum[100005], ord[100005], cnt = 0;
vector<pii> result;
// usage: edges[u] must hold (v, edge id) pairs so a parallel edge isn't
// mistaken for the parent edge
void dfs(int index, int parent_eid) {
    nodenum[index] = ord[index] = ++cnt;
    for(auto [i, eid] : edges[index]) if(eid != parent_eid) {
        if(nodenum[i] == -1) {
            dfs(i, eid);
            if(ord[i] > nodenum[index]) result.push_back({index, i});
            ord[index] = min(ord[index], ord[i]);
        }
        else ord[index] = min(ord[index], nodenum[i]);
    }
}

void SolveProblem() {
    for(int i=1; i<=n; i++) nodenum[i] = -1;
    for(int i=1; i<=n; i++) if(nodenum[i] == -1) dfs(i, -1);
}
