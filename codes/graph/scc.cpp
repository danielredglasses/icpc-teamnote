vi edges[100005];
int nodenum[100005], ord[100005], cnt = 0;
stack<int> st;
bool visited[100005] = {false};
int groupnum[100005], groupcnt = 0;

void scc(int index) {
    nodenum[index] = ord[index] = ++cnt;
    st.push(index);
    for(int i : edges[index]) {
        if(nodenum[i] == -1) {
            scc(i);
            ord[index] = min(ord[index], ord[i]);
        }
        else if(!visited[i]) ord[index] = min(ord[index], nodenum[i]);
    }
    if(ord[index] == nodenum[index]) {
        ++groupcnt;
        while(!st.empty()) {
            int cur = st.top(); st.pop();
            groupnum[cur] = groupcnt; visited[cur] = true;
            if(cur == index) break;
        }
    }
}

void SolveProblem() {
    for(int i=1; i<=n*2; i++) nodenum[i] = -1;
    for(int i=1; i<=n*2; i++) if(nodenum[i] == -1) scc(i);

    for(int i=1; i<=n; i++) if(groupnum[i*2-1] == groupnum[i*2]) {
        cout << "-1\n";
        return;
    }

    vector<pii> v;
    for(int i=1; i<=n*2; i++) v.push_back(make_pair(groupnum[i], i));
    sort(all(v));
    for(int i=0; i<n*2; i++) if(!result[(v[i].second+1)/2]) result[(v[i].second+1)/2] = v[i].second%2 == 1 ? 'R' : 'B';
    for(int i=1; i<=n; i++) cout << result[i];
    cout << "\n";
}