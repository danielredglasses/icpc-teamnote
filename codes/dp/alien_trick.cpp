int n; ll sumarr[100005];
ll cost(int l, int r) {
    ll s = sumarr[r] - sumarr[l-1];
    return s * s;
}

ll dp[100005]; int mn[100005], mx[100005];

void dp_penalty(ll lam) {
    dp[0] = 0; mn[0] = mx[0] = 0;
    for(int i=1; i<=n; i++) {
        dp[i] = 4e18;
        for(int j=0; j<i; j++) {
            ll cur = dp[j] + 2 * cost(j+1, i) + lam;
            if(cur < dp[i]) { dp[i] = cur; mn[i] = mn[j]+1; mx[i] = mx[j]+1; }
            else if(cur == dp[i]) { mn[i] = min(mn[i], mn[j]+1); mx[i] = max(mx[i], mx[j]+1); }
        }
    }
}

ll alien_trick(int k, vi &cut) {
    ll s = 0, e = 1e15;
    while(s < e) {
        ll mid = (s+e) / 2;
        dp_penalty(mid*2 + 1);
        if(mn[n] <= k) e = mid;
        else s = mid+1;
    }
    dp_penalty(s*2);
    cut.clear();
    if(k < mn[n] || k > mx[n]) return -1;
    for(int i=n, rem=k; i>0; rem--) {
        cut.push_back(i);
        for(int j=i-1; j>=0; j--) {
            if(dp[j] + 2 * cost(j+1, i) + s*2 == dp[i] && mn[j] <= rem-1 && rem-1 <= mx[j]) { i = j; break; }
        }
    }
    reverse(all(cut));
    return (dp[n] - s*2 * k) / 2;
}
