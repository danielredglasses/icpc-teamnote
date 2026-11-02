// Faker's Algorithm: n jobs form a tree rooted at 'root' (a job can only
// run after its parent has run), each job i with weight arr[i]. Among all
// orderings that respect this precedence, minimizes sum_i arr[i] *
// (completion time of i), where completion time = how many jobs have run
// up to and including i (unit processing time per job). Generalizes
// Smith's rule (for a single chain with no precedence, schedule by
// decreasing weight) to tree precedence: repeatedly take the available
// group with the largest average weight (sum/size) and merge it right
// after its parent's current group, via a lazy priority queue over
// DSU-merged groups.
struct fraction { // a / b
    ll a, b;
    fraction() { a = 0; b = 1;}
    fraction(ll _a) : a(_a) { b = 1; }
    fraction(ll _a, ll _b) : a(_a), b(_b) { }
    
    friend bool operator < (const fraction &f1, const fraction &f2) {
        return f1.a * f2.b < f2.a * f1.b;
    }
    friend bool operator > (const fraction &f1, const fraction &f2) {
        return f1.a * f2.b > f2.a * f1.b;
    }
    friend bool operator != (const fraction &f1, const fraction &f2) {
        return f1.a * f2.b != f2.a * f1.b;
    }
};

int n, root;
ll arr[1005];
vi edges[1005];

int parent[1005];
void dfs(int index, int p) {
    parent[index] = p;
    for(int i : edges[index]) if(i != p) dfs(i, index);
}

int group[1005], sz[1005];
ll sumarr[1005] = {0};
int find_group(int index) {
    return group[index] == index ? index : group[index] = find_group(group[index]);
}

ll result = 0;

void SolveProblem() {
    cin >> n >> root;
    for(int i=1; i<=n; i++) cin >> arr[i];
    for(int i=1; i<=n-1; i++) {
        int a, b; cin >> a >> b;
        edges[a].push_back(b); edges[b].push_back(a);
    }
    
    dfs(root, -1);
    
    for(int i=1; i<=n; i++) {
        group[i] = i;
        sz[i] = 1;
        sumarr[i] = arr[i];
    }
    
    priority_queue<pair<fraction, int>> pq;
    for(int i=1; i<=n; i++) pq.push({fraction(sumarr[i], sz[i]), i});
    
    for(int i=1; i<=n; i++) result += arr[i];

    while(!pq.empty()) {
        fraction f; int cur;
        tie(f, cur) = pq.top(); pq.pop();

        if(f.b != sz[cur] || cur == root) continue;

        int g = find_group(parent[cur]);
        result += sumarr[cur] * sz[g];
        
        group[cur] = g;
        sz[g] += sz[cur]; sumarr[g] += sumarr[cur];

        pq.push({fraction(sumarr[g], sz[g]), g});
    }

    cout << result << "\n";
}