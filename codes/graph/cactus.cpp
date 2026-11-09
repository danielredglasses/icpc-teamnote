// (neighbor, edge id); both directions of an edge share the same id
vector<pii> edges[100005];
int nodenum[100005], ord[100005], cnt = 0;
bool visited[100005];
vector<pii> st; // (origin vertex, edge id)
vector<int> group[100005];
int groupnum[100005], groupidx = 0;

void dfs(int index, int parent_eid) {
    nodenum[index] = ++cnt; ord[index] = cnt;
    for(auto [i, eid] : edges[index]) if(eid != parent_eid) {
        if(nodenum[i] == -1) {
            st.push_back({index, eid});
            dfs(i, eid);
            visited[i] = true;
            ord[index] = min(ord[index], ord[i]);
        }
        else if(!visited[i]) {
            ord[index] = min(ord[index], nodenum[i]);
            ++groupidx;

            st.push_back({index, eid});
            while(!st.empty()) {
                pii cur = st.back(); st.pop_back();
                group[groupidx].push_back(cur.second);
                groupnum[cur.second] = groupidx;

                if(cur.first == i) break;
            }
            sort(all(group[groupidx]));
        }
    }
    if(ord[index] == nodenum[index] && !st.empty()) {
        ++groupidx;
        pii cur = st.back(); st.pop_back();
        group[groupidx].push_back(cur.second);
        groupnum[cur.second] = groupidx;
    }
}

void SolveProblem() {
    for(int i=1; i<=n; i++) nodenum[i] = -1;
    for(int i=1; i<=n; i++) if(nodenum[i] == -1) dfs(i, -1);
}
