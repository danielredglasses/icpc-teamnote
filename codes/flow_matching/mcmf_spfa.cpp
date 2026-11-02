// Time: O(F * V * E), F = max flow value (SPFA-based shortest augmenting path)
int n, source, sink;
vi edges[405];
ll capacity[405][405], flow[405][405], cost[405][405];
bool inqueue[405]; int parent[405]; ll dist[405];

// usage: source = n+1, sink = n+2 before adding edges; returns {max_flow, min_cost}
pll mcmf() {
    ll max_flow = 0, min_cost = 0;
    memset(inqueue, false, sizeof inqueue);

    while(1) {
        fill(parent+1, parent+sink+1, 0); fill(dist+1, dist+sink+1, (ll) 4e18);
        queue<int> q; q.push(source);
        parent[source] = source; dist[source] = 0; inqueue[source] = true;
        
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            inqueue[cur] = false;
            for(int i : edges[cur]) {
                if(capacity[cur][i] - flow[cur][i] > 0 && dist[cur] + cost[cur][i] < dist[i]) {
                    parent[i] = cur; dist[i] = dist[cur] + cost[cur][i];
                    if(!inqueue[i]) {
                        inqueue[i] = true;
                        q.push(i);
                    }
                }
            }
        }

        if(!parent[sink]) break;

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