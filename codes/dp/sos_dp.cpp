for(int t=0; t<20; t++) for(int i=0; i<(1<<20); i++) if(i&(1<<t)) {
    dp[i] += dp[i^(1<<t)];
}