void calc_z() {
    z[1] = n;
    int l = 1, r = 1;
    for(int i=2; i<=n; i++) {
        z[i] = i < r ? min(r-i, z[i-l+1]) : 0;
        while(i+z[i] <= n && s1[1+z[i]] == s1[i+z[i]]) z[i]++;
        if(i+z[i] > r) { l = i; r = i+z[i]; }
    }
}

void SolveProblem() {
    cin >> s1;
    n = s1.size(); s1 = " " + s1;
    calc_z();
}
