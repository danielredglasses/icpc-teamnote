// Global min cut of an undirected graph. 'adj' is destroyed by the merges.
// usage: set n and adj[1..n][1..n] (symmetric edge weights, 0 for no edge);
// ll cut = stoer_wagner();
int n; ll adj[505][505];
bool merged[505], added[505];
ll cut_weight[505];

ll stoer_wagner() {
    ll result = 4e18;
    for(int i=1; i<=n; i++) merged[i] = false;

    for(int phase=1; phase<n; phase++) {
        for(int i=1; i<=n; i++) { 
            cut_weight[i] = 0; 
            added[i] = false; 
        }

        int prev = -1, last = -1;
        for(int it=1; it<=n-phase+1; it++) {
            int sel = -1;
            for(int i=1; i<=n; i++) if(!merged[i] && !added[i] && (sel == -1 || cut_weight[i] > cut_weight[sel])) sel = i;

            added[sel] = true;
            prev = last; last = sel;
            for(int i=1; i<=n; i++) if(!merged[i] && !added[i]) cut_weight[i] += adj[sel][i];
        }

        result = min(result, cut_weight[last]);

        merged[last] = true;
        for(int i=1; i<=n; i++) {
            adj[prev][i] += adj[last][i];
            adj[i][prev] = adj[prev][i];
        }
    }

    return result;
}
