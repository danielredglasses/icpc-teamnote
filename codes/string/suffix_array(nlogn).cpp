string s; int n;
int sa[100005], rnk[100005], tmp[100005], cnt[100005];
int ord[100005], lcp[100005];

void suffix_array() {
    int m = 256;
    fill(cnt, cnt+m+1, 0);
    for(int i=1; i<=n; i++) cnt[rnk[i] = (unsigned char) s[i]]++;
    for(int i=1; i<=m; i++) cnt[i] += cnt[i-1];
    for(int i=n; i>=1; i--) sa[cnt[rnk[i]]--] = i;
    for(int len=1; len<n; len<<=1) {
        int p = 0;
        for(int i=n-len+1; i<=n; i++) tmp[++p] = i;
        for(int i=1; i<=n; i++) if(sa[i] > len) tmp[++p] = sa[i] - len;
        fill(cnt, cnt+m+1, 0);
        for(int i=1; i<=n; i++) cnt[rnk[i]]++;
        for(int i=1; i<=m; i++) cnt[i] += cnt[i-1];
        for(int i=n; i>=1; i--) sa[cnt[rnk[tmp[i]]]--] = tmp[i];
        auto key2 = [&](int i) { return i+len <= n ? rnk[i+len] : 0; };
        tmp[sa[1]] = 1;
        for(int i=2; i<=n; i++) tmp[sa[i]] = tmp[sa[i-1]] + (rnk[sa[i-1]] != rnk[sa[i]] || key2(sa[i-1]) != key2(sa[i]));
        for(int i=1; i<=n; i++) rnk[i] = tmp[i];
        m = rnk[sa[n]];
        if(m == n) break;
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
