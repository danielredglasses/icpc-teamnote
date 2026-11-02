// dp[i][j] = \min_{i<=k<j}(dp[i][k] + dp[k+1][j] + cost(i, j));
// requires cost to satisfy the quadrangle inequality
// Time: O(n^2), down from the naive O(n^3) interval dp
for(int l=1; l<=n; l++) {
    for(int i=1; i+l-1<=n; i++) {
        if(l == 1) { dp[i][i] = 0; opt[i][i] = i; }
        else {
            int j = i+l-1;
            opt[i][j] = -1;
            for(int k=max(opt[i][j-1], i); k<j && k<=opt[i+1][j]; k++) {
                if(opt[i][j] == -1 || dp[i][j] > dp[i][k] + dp[k+1][j] + cost(i, j)) {
                    dp[i][j] = dp[i][k] + dp[k+1][j] + cost(i, j);
                    opt[i][j] = k;
                }
            }
        }
    }
}
