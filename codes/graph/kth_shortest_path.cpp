struct node { // persistent leftist heap
    ll key; int rank, value;
    int l, r; // 0 = null
};

// size ~ E * log2(E); shrink it to fit the memory limit
node heap[2000005]; int heap_cnt = 0;

int new_node(int rank, ll key, int value, int l, int r) {
    int cur = ++heap_cnt;
    heap[cur] = {key, rank, value, l, r};
    return cur;
}

int insert(int cur, ll key, int value) {
    if(!cur || key < heap[cur].key) return new_node(1, key, value, cur, 0);
    int l = heap[cur].l, r = insert(heap[cur].r, key, value);
    if(!l || heap[r].rank > heap[l].rank) swap(l, r);
    return new_node(r ? heap[r].rank+1 : 1, heap[cur].key, heap[cur].value, l, r);
}

int n;
vector<pll> edges[250005], revedges[250005];
vi edges1[250005];

ll dist[250005]; int parent[250005];
int nodes[250005];
void dijkstra(int e) {
    for(int i=1; i<=n; i++) { dist[i] = 1e18; parent[i] = -1; }
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>> > pq;
    dist[e] = 0; pq.push({dist[e], e});
    while(!pq.empty()) {
        pair<ll, int> tmp = pq.top(); pq.pop();
        if(tmp.first > dist[tmp.second]) continue;

        int cur = tmp.second;
        for(pll e : revedges[cur]) if(dist[cur] + e.second < dist[e.first]) {
            dist[e.first] = dist[cur] + e.second;
            parent[e.first] = cur;
            pq.push({dist[e.first], e.first});
        }
    }
}

ll result[250005];
void find_k_shortest_walk(int s, int e, int k) {
    for(int i=1; i<=k; i++) result[i] = -1;

    for(int i=1; i<=n; i++) for(pll e : edges[i]) revedges[e.first].push_back({i, e.second});
    dijkstra(e);

    if(dist[s] == 1e18) return;

    for(int i=1; i<=n; i++) if(parent[i] != -1) edges1[parent[i]].push_back(i);

    queue<int> q; q.push(e);
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        bool flag = false;
        for(pll e : edges[cur]) {
            if(dist[e.first] == 1e18) continue;
            ll cost = e.second + dist[e.first] - dist[cur];
            if(!flag && e.first == parent[cur] && cost == 0) {
                flag = true;
                continue;
            }
            nodes[cur] = insert(nodes[cur], cost, e.first);
        }
        for(int nx : edges1[cur]) {
            nodes[nx] = nodes[cur];
            q.push(nx);
        }
    }

    result[1] = dist[s];

    if(!nodes[s]) return;

    priority_queue<pll, vector<pll>, greater<pll> > pq;
    pq.push({dist[s] + heap[nodes[s]].key, nodes[s]});

    for(int i=2; i<=k && !pq.empty(); i++) {
        pll cur = pq.top(); pq.pop();
        result[i] = cur.first;

        int curnode = cur.second;
        if(nodes[heap[curnode].value]) pq.push({cur.first + heap[nodes[heap[curnode].value]].key, nodes[heap[curnode].value]});
        if(heap[curnode].l) pq.push({cur.first + heap[heap[curnode].l].key - heap[curnode].key, heap[curnode].l});
        if(heap[curnode].r) pq.push({cur.first + heap[heap[curnode].r].key - heap[curnode].key, heap[curnode].r});
    }
}