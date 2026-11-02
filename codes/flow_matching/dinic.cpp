// Time: O(V^2 E) general graphs; O(E sqrt(V)) for unit-capacity graphs
// (e.g. bipartite matching)
const int MAXV = 505;
ll capacity[MAXV][MAXV], flow[MAXV][MAXV];
vi edges[MAXV]; int level[MAXV], idx[MAXV], source, sink, teamnum[MAXV]; ll result = 0;

bool find_level() {
    memset(level, -1, sizeof level);
    queue<int> q; q.push(source);
    level[source] = 0;
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int i : edges[cur]) {
            if(level[i] == -1 && capacity[cur][i] - flow[cur][i] > 0) {
                level[i] = level[cur] + 1;
                q.push(i);
            }
        }
    }
    return level[sink] != -1;
}
ll find_flow(int cur, ll curflow) {
    if(cur == sink) return curflow;
    for(int &i = idx[cur]; i<edges[cur].size(); i++) {
        int nx = edges[cur][i];
        if(capacity[cur][nx] - flow[cur][nx] > 0 && level[nx] == level[cur] + 1) {
            ll amount = find_flow(nx, min(curflow, capacity[cur][nx] - flow[cur][nx]));
            if(amount > 0) {
                flow[cur][nx] += amount;
                flow[nx][cur] -= amount;
                return amount;
            }
        }
    }
    return 0;
}

void find_team() {
    queue<int> q; q.push(source);
    teamnum[source] = 1;
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int i : edges[cur]) {
            if(!teamnum[i] && capacity[cur][i] - flow[cur][i] > 0) {
                teamnum[i] = 1;
                q.push(i);
            }
        }
    }
}

void SolveProblem() {
    while(find_level()) {
        memset(idx, 0, sizeof idx);
        while(1) {
            ll amount = find_flow(source, 1e9);
            if(amount == 0) break;
            result += amount;
        }
    }
    find_team();
}