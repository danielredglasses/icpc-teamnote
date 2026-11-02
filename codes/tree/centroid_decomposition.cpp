void find_sz(int index, int p) {
    sz[index] = 1;
    for(int i : edges[index]) if(i != p && !visited[i]) {
        find_sz(i, index);
        sz[index] += sz[i];
    }
}

int find_centroid(int index, int p, int cursz) {
    for(int i : edges[index]) if(i != p && !visited[i]) {
        if(sz[i]*2 > cursz) return find_centroid(i, index, cursz);
    }
    return index;
}

void dfs(int index, int parent) {
    // ... gather/query info within the centroid's current component
    // (fill in per-problem)
}

void centroid_dnc(int index) {
    find_sz(index, -1);
    
    int centroid = find_centroid(index, -1, sz[index]);
    for(int i : edges[centroid]) if(!visited[i]) {
        // v.clear();
        dfs(i, centroid);
        // ...
    }
    
    visited[centroid] = true;
    for(int i : edges[centroid]) if(!visited[i]) centroid_dnc(i);
}