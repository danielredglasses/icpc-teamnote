const ll MOD1 = 1e9+7, MOD2 = 998244353;
const ll p1 = 19192734, p2 = 603820;
ll exp_p1[200005], exp_p2[200005];

void precompute_pow() {
    exp_p1[0] = exp_p2[0] = 1;
    for(int i=1; i<200005; i++) { exp_p1[i] = exp_p1[i-1] * p1 % MOD1; exp_p2[i] = exp_p2[i-1] * p2 % MOD2; }
}

void find_sz(int index, int p) {
    sz[index] = 1;
    for(int i : edges[index]) if(i != p) {
        find_sz(i, index);
        sz[index] += sz[i];
    }
}

void find_centroid(int index, int p) {
    bool valid = true;
    for(int i : edges[index]) if(i != p) {
        if(sz[i] * 2 >= m) find_centroid(i, index);
        if(sz[i] * 2 > m) valid = false;
    }
    
    if(valid) centroid.push_back(index);
}

void find_hash(int index, int p) {
    // "(" : 28, ")": 29
    hash_tree[index] = {28, 28};
    
    vector<pair<pll, int> > v;
    for(int i : edges[index]) if(i != p) {
        find_hash(i, index);
        v.push_back({hash_tree[i], i});
    }
    sort(all(v));
    
    int cur_sz = 1;
    for(int i=0; i<v.size(); i++) {
        pll a = v[i].first; int idx = v[i].second;
        hash_tree[index].first = (hash_tree[index].first + exp_p1[cur_sz] * a.first % MOD1) % MOD1;
        hash_tree[index].second = (hash_tree[index].second + exp_p2[cur_sz] * a.second % MOD2) % MOD2;
        cur_sz += sz[idx]*2;
    }
    
    hash_tree[index].first = (hash_tree[index].first + exp_p1[cur_sz] * 29 % MOD1) % MOD1;
    hash_tree[index].second = (hash_tree[index].second + exp_p2[cur_sz] * 29 % MOD2) % MOD2;
}

void SolveProblem() {
    precompute_pow();
    find_sz(1, -1);

    centroid.clear();
    find_centroid(1, -1);
    
    if(centroid.size() == 2) {
        int a = centroid[0], b = centroid[1];
        for(int i=0; i<edges[a].size(); i++) if(edges[a][i] == b) {
            edges[a].erase(edges[a].begin() + i);
            break;
        }
        for(int i=0; i<edges[b].size(); i++) if(edges[b][i] == a) {
            edges[b].erase(edges[b].begin() + i);
            break;
        }
        edges[a].push_back(m+1); edges[m+1].push_back(a);
        edges[b].push_back(m+1); edges[m+1].push_back(b);
    }

    int cur = centroid.size() == 1 ? centroid[0] : m+1;
    find_sz(cur, -1);
    find_hash(cur, -1);
}