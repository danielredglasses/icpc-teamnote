// dp[i][j] = \min_{k<j}(dp[i-1][k] + cost[k][j]); requires opt(j) to be
// non-decreasing in j
// Time: O(n log n) per row (O(n) rows -> O(n^2 log n) total for the full 2D dp)
ll cost(int a, int b) {
    ll dx = c[a].first - p[b].first, dy = c[a].second - p[b].second;
    return dx < 0 && dy < 0 ? 0 : dx * dy;
}

void DnC(int l, int r, int s, int e) {
    if(l > r) return;
    int mid = (l+r)/2, opt = l;
    
    for(int i=s; i<=e; i++) if(cost(i, mid) < cost(opt, mid)) opt = i;
    dp[mid] = cost(opt, mid);
    
    DnC(l, mid-1, s, opt); DnC(mid+1, r, opt, e);
}