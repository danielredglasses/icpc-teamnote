// Split [1..n] into exactly k groups, minimizing the total cost.
// Requires f(k) = (optimal cost with k groups) to be convex in k.
// Binary search a penalty 'lam' charged per group, solve the unconstrained dp,
// then undo the penalty.
// Time: O(n^2 log V) with the naive O(n^2) inner dp below
// (V = search range for lam);
// O(n log n log V) if the inner dp is sped up with CHT / DnC /
// monotone deque instead
// (cost() here also satisfies the quadrangle inequality needed for those).
// usage: set n and sumarr[] (1-indexed prefix sums), then ll ans = alien_trick(k);

// example cost: minimize the sum of (group sum)^2, given prefix sums sumarr[]
ll sumarr[100005];
ll cost(int l, int r) { 
    ll s = sumarr[r] - sumarr[l-1]; 
    return s * s; 
}

ll dp[100005]; int cnt[100005];

// O(n^2): try every previous split point j for each i
pair<ll, int> dp_penalty(ll lam) {
    dp[0] = 0; cnt[0] = 0;
    for(int i=1; i<=n; i++) {
        dp[i] = 4e18; cnt[i] = 0;
        for(int j=0; j<i; j++) {
            ll cur = dp[j] + cost(j+1, i) + lam;
            // on a tie, keep the smallest number of groups
            if(cur < dp[i] || (cur == dp[i] && cnt[j]+1 < cnt[i])) {
                dp[i] = cur; cnt[i] = cnt[j]+1;
            }
        }
    }
    return {dp[n], cnt[n]};
}

// O(log V) calls to dp_penalty, so O(n^2 log V) total with the O(n^2) dp above
ll alien_trick(int k) {
    ll s = 0, e = 1e15; // e >= max gap f(k-1) - f(k)
    while(s < e) {
        ll mid = (s+e) / 2;
        if(dp_penalty(mid).second <= k) e = mid;
        else s = mid+1;
    }
    return dp_penalty(s).first - s * k;
}
