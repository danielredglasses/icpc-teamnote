string s;
int n;
int groupnum[100005], nx[100005], sa[100005];
int ord[100005], lcp[100005];

ll result = 0;

int len = 1;
bool cmp_sa(int x, int y) {
    if(groupnum[x] == groupnum[y]) {
        if(x+len > n && y+len > n) return true;
        else if(x+len > n) return true;
        else if(y+len > n) return false;
        else return groupnum[x+len] < groupnum[y+len];
    }
    return groupnum[x] < groupnum[y];
}

void suffix_array() {
    for(int i=1; i<=n; i++) sa[i] = i;
    for(int i=1; i<=n; i++) groupnum[i] = s[i] - 'a';
    len = 1;
    while(len <= n) {
        for(int i=1; i<=n; i++) nx[i] = 0;
        sort(sa+1, sa+n+1, cmp_sa);
        for(int i=2; i<=n; i++) nx[sa[i]] = nx[sa[i-1]] + cmp_sa(sa[i-1], sa[i]);
        for(int i=1; i<=n; i++) groupnum[i] = nx[i];
        len = len * 2;
    }
}

void find_lcp() {
    for(int i=1; i<=n; i++) ord[sa[i]] = i;
    
    int l=0;
    for(int i=1; i<=n; i++) {
        int k = ord[i];
        if(k > 1) {
            int j = sa[k-1];
            while(s[i+l] == s[j+l]) l++;
            lcp[k] = l;
            if(l) l--;
        }
    }
}