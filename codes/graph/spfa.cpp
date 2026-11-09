int n;
vector<pll> edges[100005];
ll dist[100005]; int cnt[100005]; bool inqueue[100005];

bool spfa(int s) {
    for(int i=1; i<=n; i++) { dist[i] = 4e18; cnt[i] = 0; inqueue[i] = false; }
    queue<int> q; q.push(s);
    dist[s] = 0; inqueue[s] = true;
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        inqueue[cur] = false;
        for(auto [nxt, w] : edges[cur]) {
            if(dist[cur] + w < dist[nxt]) {
                dist[nxt] = dist[cur] + w;
                cnt[nxt] = cnt[cur] + 1;
                if(cnt[nxt] >= n) return false;
                if(!inqueue[nxt]) { inqueue[nxt] = true; q.push(nxt); }
            }
        }
    }
    return true;
}
