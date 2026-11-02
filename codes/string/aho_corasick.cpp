struct Trie {
    map<int, int> child;
    int fail;
    bool isend; int isend_cnt;
    Trie() {
        fail = 0;
        isend = false; isend_cnt = 0;
    }
};

Trie nodes[305]; int node_cnt = 0;
int root;

void insert(string &s, int cur, int index) {
    if(s.size() == index) {
        nodes[cur].isend = true;
        nodes[cur].isend_cnt++;
        return;
    }
    
    int x = s[index]-'A'+1; // 1-indexed: 'A'..'Z' -> 1..26
    if(!nodes[cur].child.count(x)) nodes[cur].child[x] = ++node_cnt;
    insert(s, nodes[cur].child[x], index+1);
}

void Aho_Corasick() {
    queue<int> q; q.push(root);
    nodes[root].fail = root;
    
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(auto [i, next] : nodes[cur].child) {
            if(cur == root) nodes[next].fail = root;
            else {
                int dest = nodes[cur].fail;
                while(dest != root && !nodes[dest].child.count(i)) dest = nodes[dest].fail;
                if(nodes[dest].child.count(i)) dest = nodes[dest].child[i];
                nodes[next].fail = dest;
            }
            
            if(nodes[nodes[next].fail].isend) {
                nodes[next].isend = true;
                nodes[next].isend_cnt += nodes[nodes[next].fail].isend_cnt;
            }
            
            q.push(next);
        }
    }
}

void SolveProblem() { // nx_node[][] must be sized for indices 1..26
    root = ++node_cnt;
    for(int j=1; j<=node_cnt; j++) for(int k=1; k<=26; k++) {
        int cur = j;
        while(cur != root && !nodes[cur].child.count(k)) cur = nodes[cur].fail;
        if(nodes[cur].child.count(k)) {
            cur = nodes[cur].child[k];
            nx_node[j][k] = cur;
        }
        else nx_node[j][k] = root;
    }
}