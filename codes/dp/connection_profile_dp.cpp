// Time: O(n*m*B_m) where B_m is the m-th Bell number
// (number of distinct profile states), exponential in m
int n, m;
ll arr[15][15];
map<string, ll> dp[15][15];
ll result = 1e18;

void init() {
    string tmp = "";
    for(int i=1; i<=m; i++) tmp += '0';
    dp[0][m][tmp] = 0;
}

bool isvalid(string state) {
    if(state[0] == '0') return true;
    for(int i=1; i<m; i++) if(state[i] == state[0]) return true;
    return false;
}

string norm(string state) {
    int num[10] = {0}; int cnt = 0;
    for(int i=0; i<m; i++) {
        if(state[i] == '0') continue;
        if(!num[state[i]-'0']) num[state[i]-'0'] = ++cnt;
        state[i] = (char) ('0' + num[state[i]-'0']);
    }
    return state;
}

string merge(int x, int y, string state) {
    if(y == 1) {
        if(state[0] == '0') state += '9';
        else state += state[0];
    }
    else {
        if(state[0] == '0' && state[m-1] == '0') state += '9';
        else if(state[0] == '0') state += state[m-1];
        else if(state[m-1] == '0') state += state[0];
        else {
            state += state[0];
            for(int i=1; i<m; i++) if(state[i] == state[m-1]) state[i] = state[0]; 
        }
    }
    state.erase(state.begin());
    return norm(state);
}

void update(int x, int y, string state, ll val) {
    if(!dp[x][y].count(state)) dp[x][y][state] = val;
    else dp[x][y][state] = min(dp[x][y][state], val);
}

int groupnum(string state) {
    bool check[10] = {false}; int cnt = 0;
    for(int i=0; i<m; i++) {
        if(state[i] == '0' || check[state[i]-'0']) continue;
        check[state[i]-'0'] = true;
        cnt++;
    }
    return cnt;
}

void SolveProblem() {
    cin >> n >> m;
    for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) cin >> arr[i][j];

    init();

    for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) {
        int px = j == 1 ? i-1 : i, py = j == 1 ? m : j-1;
        for(auto it = dp[px][py].begin(); it != dp[px][py].end(); ++it) {
            string curstate = it->first;
            if(isvalid(curstate)) {
                string nxstate = curstate; nxstate.erase(nxstate.begin());
                nxstate += '0';
                update(i, j, nxstate, it->second);
            }
            string nxstate = merge(i, j, curstate);
            update(i, j, nxstate, it->second + arr[i][j]);
        }
    }
    
    for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) {
        for(auto it = dp[i][j].begin(); it != dp[i][j].end(); ++it) {
            int cnt = groupnum(it->first);
            if(cnt <= 1) result = min(result, it->second);
        }
    }

    cout << result << "\n";
}