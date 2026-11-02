// Palindromic tree (eertree). s must be 1-indexed. Time: O(n) amortized.
// Number of distinct palindromic substrings = node_cnt - 2.
struct node {
    int len, suffix;
    int child[27];
};

node nodes[100005]; int node_cnt = 0;
int root_neg, root_zero, last;
string s;

int new_node(int len, int suffix) {
    int cur = ++node_cnt;
    nodes[cur].len = len; nodes[cur].suffix = suffix;
    memset(nodes[cur].child, 0, sizeof nodes[cur].child);
    return cur;
}

void init() {
    root_neg = new_node(-1, 0);        // imaginary root, len -1
    nodes[root_neg].suffix = root_neg;
    root_zero = new_node(0, root_neg); // empty root, len 0
    last = root_zero;
}

// add s[idx], returns the node of the longest palindromic suffix
int insert(int idx) {
    int cur = last;
    while(idx-nodes[cur].len-1 < 1 || s[idx-nodes[cur].len-1] != s[idx]) cur = nodes[cur].suffix;

    int c = s[idx] - 'a' + 1;
    if(nodes[cur].child[c]) return last = nodes[cur].child[c];

    int nx = new_node(nodes[cur].len + 2, root_zero);
    if(nodes[nx].len > 1) {
        int tmp = nodes[cur].suffix;
        while(idx-nodes[tmp].len-1 < 1 || s[idx-nodes[tmp].len-1] != s[idx]) tmp = nodes[tmp].suffix;
        nodes[nx].suffix = nodes[tmp].child[c];
    }
    nodes[cur].child[c] = nx;

    return last = nx;
}

void SolveProblem() {
    cin >> s; s = " " + s;
    init();
    for(int i=1; i<s.size(); i++) insert(i);
}
