int connected[200005], rev_connected[200005];
bool visited[200005] = {false}; int dist[200005] = {0};
void bfs() {
    queue<int> q;
    for(int i=1; i<=n; i++) {
        visited[i] = false;
        if(connected[i] == -1) {
            dist[i] = 0;
            q.push(i);
        }
        else dist[i] = 1e9;
    }

    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int i : edges[cur]) {
            if(rev_connected[i] != -1 && dist[rev_connected[i]] == 1e9) {
                dist[rev_connected[i]] = dist[cur] + 1;
                q.push(rev_connected[i]);
            }
        }
    }
}

bool bip_match(int index) {
    if(visited[index]) return false;
    visited[index] = true;

    for(int i : edges[index]) {
        if(rev_connected[i] == -1 || dist[rev_connected[i]] == dist[index] + 1 && bip_match(rev_connected[i])) {
            connected[index] = i;
            rev_connected[i] = index;
            return true;
        }
    }
    return false;
}

bool team_l[200005], team_r[200005];
// usage: after matching, team_l[i] / team_r[i] = true if on the source side of min cut
void find_team() {
    queue<int> q;
    for(int i=1; i<=n; i++) {
        team_l[i] = connected[i] == -1;
        if(team_l[i]) q.push(i);
    }
    for(int i=1; i<=m; i++) team_r[i] = false;

    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int i : edges[cur]) {
            if(team_r[i]) continue;
            team_r[i] = true;
            team_l[rev_connected[i]] = true;
            q.push(rev_connected[i]);
        }
    }
}

void SolveProblem() {
    for(int i=1; i<=n; i++) connected[i] = -1;
    for(int i=1; i<=m; i++) rev_connected[i] = -1;
    while(1) {
        bfs();

        bool flag = false;
        for(int i=1; i<=n; i++) if(connected[i] == -1 && bip_match(i)) flag = true;

        if(!flag) break;
    }
    find_team();
}
