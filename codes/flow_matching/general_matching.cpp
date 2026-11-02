// Maximum matching on a general graph (Blossom algorithm), O(V^3)
// usage: set n and edges[u] (undirected, add both directions);
// int m = general_matching();
// match[i] = i's partner (-1 if unmatched)
int n;
vi edges[505];
int match[505], p[505], base[505];
bool used[505], blossom[505];

void mark_path(int v, int b, int child) {
    while(base[v] != b) {
        blossom[base[v]] = true;
        blossom[base[match[v]]] = true;
        p[v] = child;
        child = match[v];
        v = p[match[v]];
    }
}

int lca(int a, int b) {
    static bool used_lca[505];
    memset(used_lca, false, sizeof used_lca);

    int v = a;
    while(1) {
        v = base[v]; used_lca[v] = true;
        if(match[v] == -1) break;
        v = p[match[v]];
    }

    v = b;
    while(1) {
        v = base[v];
        if(used_lca[v]) return v;
        v = p[match[v]];
    }
}

// returns the endpoint of an augmenting path from 'root', -1 if none
int find_path(int root) {
    memset(used, false, sizeof used);
    memset(p, -1, sizeof p);
    for(int i=1; i<=n; i++) base[i] = i;

    used[root] = true;
    queue<int> q; q.push(root);
    while(!q.empty()) {
        int v = q.front(); q.pop();
        for(int to : edges[v]) {
            if(base[v] == base[to] || match[v] == to) continue;

            if(to == root || (match[to] != -1 && p[match[to]] != -1)) {
                int curbase = lca(v, to);
                memset(blossom, false, sizeof blossom);
                mark_path(v, curbase, to);
                mark_path(to, curbase, v);
                for(int i=1; i<=n; i++) if(blossom[base[i]]) {
                    base[i] = curbase;
                    if(!used[i]) { used[i] = true; q.push(i); }
                }
            }
            else if(p[to] == -1) {
                p[to] = v;
                if(match[to] == -1) return to;
                used[match[to]] = true; q.push(match[to]);
            }
        }
    }
    return -1;
}

int general_matching() {
    for(int i=1; i<=n; i++) match[i] = -1;

    for(int i=1; i<=n; i++) if(match[i] == -1) {
        int v = find_path(i);
        while(v != -1) {
            int pv = p[v], ppv = match[pv];
            match[v] = pv; match[pv] = v;
            v = ppv;
        }
    }

    int result = 0;
    for(int i=1; i<=n; i++) if(match[i] != -1) result++;
    return result / 2;
}
