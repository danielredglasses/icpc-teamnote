int n, source, sink;
vi edges[405];
ll capacity[405][405], flow[405][405], cost[405][405];
ll dist[405], pi[405]; int parent[405]; bool visited[405];

void setpi() { // one Bellman-Ford pass; only needed if some cost[][] starts negative
    fill(pi+1, pi+sink+1, (ll) 4e18); pi[source] = 0;
    for(int cnt=1; cnt<=sink; cnt++) {
        bool changed = false;
        for(int i=1; i<=sink; i++) if(pi[i] < (ll) 4e18) for(int j : edges[i]) if(capacity[i][j] > 0) {
            ll v = pi[i] + cost[i][j];
            if(v < pi[j]) { pi[j] = v; changed = true; }
        }
        if(!changed) break;
    }
}

bool dijkstra() {
    fill(dist+1, dist+sink+1, (ll) 4e18);
    fill(visited+1, visited+sink+1, false);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    dist[source] = 0; pq.push({0, source});
    while(!pq.empty()) {
        auto [d, cur] = pq.top(); pq.pop();
        if(visited[cur]) continue;
        visited[cur] = true;
        for(int i : edges[cur]) {
            if(capacity[cur][i] - flow[cur][i] <= 0) continue;
            ll nd = d + cost[cur][i] + pi[cur] - pi[i]; // reduced cost, always >= 0
            if(nd < dist[i]) { dist[i] = nd; parent[i] = cur; pq.push({nd, i}); }
        }
    }
    for(int i=1; i<=sink; i++) if(dist[i] < (ll) 4e18) pi[i] += dist[i];
    return dist[sink] < (ll) 4e18;
}

// usage: source = n+1, sink = n+2 before adding edges; returns {max_flow, min_cost}
pll mcmf() {
    ll max_flow = 0, min_cost = 0;
    while(dijkstra()) {
        ll amount = (ll) 4e18;
        for(int p=sink; p!=source; p=parent[p]) amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);
        for(int p=sink; p!=source; p=parent[p]) {
            min_cost += amount * cost[parent[p]][p];
            flow[parent[p]][p] += amount;
            flow[p][parent[p]] -= amount;
        }
        max_flow += amount;
    }
    return {max_flow, min_cost};
}
