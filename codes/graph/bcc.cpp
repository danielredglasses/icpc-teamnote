// (neighbor, edge id); both directions of an edge share the same id
vector<pii> edges[100005];
int nodenum[100005], ord[100005], cnt = 0;
stack<int> st;

int edge_group[100005], groupcnt = 0;

int bcc(int index, int parent_eid) {
    nodenum[index] = ord[index] = ++cnt;
    for(auto [i, eid] : edges[index]) if(eid != parent_eid) {
        if(nodenum[index] > nodenum[i]) st.push(eid);

        if(nodenum[i] != -1) ord[index] = min(ord[index], nodenum[i]);
        else {
            ord[index] = min(ord[index], bcc(i, eid));
            if(ord[i] >= nodenum[index]) {
                groupcnt++;
                while(!st.empty()) {
                    int cur = st.top(); st.pop();
                    edge_group[cur] = groupcnt;
                    if(cur == eid) break;
                }
            }
        }
    }
    return ord[index];
}

void SolveProblem() {
    for(int i=1; i<=n; i++) nodenum[i] = -1;
    for(int i=1; i<=n; i++) if(nodenum[i] == -1) bcc(i, -1);
}