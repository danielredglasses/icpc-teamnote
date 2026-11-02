// S(k,x) = sum_{i=0}^{x} i^k mod p, for every k = 0..n at once
// (needs an NTT-friendly MOD set via Poly<ll>::set_mod)
// Time: O(n log n)
vl power_sums(ll x, int n) {
    ll xp1 = (x+1) % MOD, pw = xp1;
    vl A1(n+1), B1(n+1);
    for(int k=0; k<=n; k++) {
        A1[k] = pw * fact_inv[k+1] % MOD;
        pw = pw * xp1 % MOD;
        B1[k] = fact_inv[k+1];
    }

    Poly<ll> C = Poly<ll>(A1).mulmod(Poly<ll>(B1).invmod(n+1)).resize(n+1);

    vl result(n+1);
    for(int k=0; k<=n; k++) result[k] = C[k] * fact[k] % MOD;
    return result;
}

// Stirling numbers of the 2nd kind, row n: returns {S(n,0), ..., S(n,n)}
// Time: O(n log n)
vl stirling2_row(int n) {
    vl f(n+1), g(n+1); // f[j] = (-1)^j/j!, g[i] = i^n/i!
    for(int j=0; j<=n; j++) f[j] = (j&1) ? (MOD - fact_inv[j]) % MOD : fact_inv[j];
    for(int i=0; i<=n; i++) g[i] = Poly<ll>::powers(i, n) * fact_inv[i] % MOD;

    return Poly<ll>(f).mulmod(Poly<ll>(g)).resize(n+1).coef;
}
