int n;
int max_match = 0;
ll cost[505][505];
ll label_x[505], label_y[505];
int match_x[505], match_y[505];
pll slack[505];
bool S[505], T[505]; 
int parent[505];

void init_label() {
    for(int i=1; i<=n; i++) label_x[i] = label_y[i] = 0;
    for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) label_x[i] = max(label_x[i], cost[i][j]);
}

void update_label() {
    ll min_label = 1e18;
    for(int j=1; j<=n; j++) if(!T[j]) min_label = min(min_label, slack[j].first);
    
    for(int i=1; i<=n; i++) if(S[i]) label_x[i] -= min_label;
    for(int j=1; j<=n; j++) if(T[j]) label_y[j] += min_label;
    
    for(int j=1; j<=n; j++) if(!T[j]) slack[j].first -= min_label;
}

void add_to_tree(int cur, int p) {
    S[cur] = true; parent[cur] = p;
    for(int j=1; j<=n; j++) if(label_x[cur] + label_y[j] - cost[cur][j] < slack[j].first) {
        slack[j].first = label_x[cur] + label_y[j] - cost[cur][j];
        slack[j].second = cur;
    }
}

void augment() {
    if(max_match == n) return;
    int x, y = n+1, root;
    for(int i=1; i<=n; i++) {
        S[i] = T[i] = false;
        parent[i] = -1;
    }
    
    queue<int> q;
    for(int i=1; i<=n; i++) if(match_x[i] == -1) {
        root = i; parent[root] = -2; S[root] = true;
        q.push(root);
        break;
    }
    
    for(int j=1; j<=n; j++) slack[j] = {label_x[root] + label_y[j] - cost[root][j], root};

    while(1) {
        while(!q.empty()) {
            x = q.front(); q.pop();
            
            for(int j=1; j<=n; j++) {
                if(label_x[x] + label_y[j] - cost[x][j] == 0 && !T[j]) {
                    if(match_y[j] == -1) {
                        y = j;
                        break;
                    }
                    T[j] = true;
                    q.push(match_y[j]);
                    add_to_tree(match_y[j], x);
                }
            }
            
            if(y <= n) break;
        }
        
        if(y <= n) break;
        update_label();
        while(!q.empty()) q.pop();
        
        for(int j=1; j<=n; j++) {
            if(slack[j].first == 0 && !T[j]) {
                if(match_y[j] == -1) {
                    x = slack[j].second;
                    y = j;
                    break;
                }
                else {
                    T[j] = true;
                    if(!S[match_y[j]]) {
                        q.push(match_y[j]);
                        add_to_tree(match_y[j], slack[j].second);
                    }
                }
            }
        }
        
        if(y <= n) break;
    }
    
    if(y <= n) {
        max_match++;
        for(int cx = x, cy = y, ty; cx != -2; cx = parent[cx], cy = ty) {
            ty = match_x[cx];
            match_x[cx] = cy; match_y[cy] = cx;
        }
        augment();
    }
}

ll hungarian() {
    for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) cost[i][j] = -cost[i][j];
    
    max_match = 0;
    for(int i=1; i<=n; i++) match_x[i] = match_y[i] = -1;
    init_label();
    augment();
    
    ll result = 0;
    for(int i=1; i<=n; i++) result += cost[i][match_x[i]];
    
    return -result;
}