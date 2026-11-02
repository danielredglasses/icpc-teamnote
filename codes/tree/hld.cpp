int parent[500005], depth[500005], sz[500005];
int chain_num[500005], chain_idx[500005];
int in[500005], out[500005]; int cnt = 0;
vi chain[500005];

void dfs(int index, int p, int d) {
    parent[index] = p; depth[index] = d;
    sz[index] = 1;
    for(int i : edges[index]) if(i != p) {
        dfs(i, index, d+1);
        sz[index] += sz[i];
    }
}

void hld(int index, int p, int cur_chain) {
    chain_num[index] = cur_chain;
    chain_idx[index] = chain[cur_chain].size();
    chain[cur_chain].push_back(index);
    
    in[index] = ++cnt;
    
    int heavy = -1;
    for(int i : edges[index]) if(i != p && (heavy == -1 || sz[i] > sz[heavy])) heavy = i;
    
    if(heavy != -1) hld(heavy, index, cur_chain);
    for(int i : edges[index]) if(i != p && i != heavy) hld(i, index, i);
    
    out[index] = cnt;
}

void SolveProblem() {
    dfs(1, -1, 0);
    hld(1, -1, 1);
}