ll mod_pow(ll x, ll p) {
    ll ret = 1; x %= MOD;
    for(; p; p>>=1, x = x * x % MOD) if(p & 1) ret = ret * x % MOD;
    return ret;
}

vector<vl> gaussian_elimination(vector<vl> a) {
    int n = a.size(), m = n ? a[0].size() : 0, row = 0;
    for(auto &v : a) for(auto &x : v) x = (x % MOD + MOD) % MOD;
    for(int col=0; col<m && row<n; col++) {
        int piv = row;
        while(piv < n && !a[piv][col]) piv++;
        if(piv == n) continue;
        swap(a[row], a[piv]);
        ll inv = mod_pow(a[row][col], MOD-2);
        for(int j=0; j<m; j++) a[row][j] = a[row][j] * inv % MOD;
        for(int i=0; i<n; i++) if(i != row && a[i][col]) {
            ll f = a[i][col];
            for(int j=0; j<m; j++) a[i][j] = ((a[i][j] - f * a[row][j]) % MOD + MOD) % MOD;
        }
        row++;
    }
    return a;
}

ll calc_det(vector<vl> a) {
    int n = a.size();
    ll det = 1;
    for(auto &v : a) for(auto &x : v) x = (x % MOD + MOD) % MOD;
    for(int col=0; col<n; col++) {
        int piv = col;
        while(piv < n && !a[piv][col]) piv++;
        if(piv == n) return 0;
        if(piv != col) { swap(a[col], a[piv]); det = (MOD - det) % MOD; }
        det = det * a[col][col] % MOD;
        ll inv = mod_pow(a[col][col], MOD-2);
        for(int i=col+1; i<n; i++) if(a[i][col]) {
            ll f = a[i][col] * inv % MOD;
            for(int j=col; j<n; j++) a[i][j] = ((a[i][j] - f * a[col][j]) % MOD + MOD) % MOD;
        }
    }
    return det;
}
