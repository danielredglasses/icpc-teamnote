int nodenum[100005], ord[100005], cnt = 0;
bool iscut[100005] = {false};

void dfs(int index, int p) {
    nodenum[index] = ord[index] = ++cnt;
    
    int children = 0;
    for(int i : edges[index]) if(i != p) {
        if(nodenum[i] == -1) {
            children++;
            dfs(i, index);
            if(p != -1 && ord[i] >= nodenum[index]) iscut[index] = true;
            ord[index] = min(ord[index], ord[i]);
        }
        else ord[index] = min(ord[index], nodenum[i]);
    }
    
    if(p == -1) iscut[index] = children >= 2;
}

void SolveProblem() {
    for(int i=1; i<=n; i++) nodenum[i] = -1;
    for(int i=1; i<=n; i++) if(nodenum[i] == -1) dfs(i, -1);
}