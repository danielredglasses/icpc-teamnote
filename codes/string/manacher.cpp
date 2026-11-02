string arr = " ";
arr += '#';
for(int i=1; i<=n; i++) {
    arr += s[i];
    arr += '#';
}

int r = 0, j = 0;
for (int i=1; i<=n*2+1; i++) {
    if (r < i) dp[i] = 0;
    else {
        int i_prime = 2*j - i;
        dp[i] = min (r-i, dp[i_prime]);
    }
    while (i-dp[i]-1 >= 1 && i+dp[i]+1 <= n*2+1 && arr[i-dp[i]-1] == arr[i+dp[i]+1]) dp[i]++;
    if (dp[i] + i > r) { r = dp[i] + i; j = i; }
}