// N-th term (0-indexed) of dp[i+k] = sum_j c[j]*dp[i+j], via x^N mod f(x),
// f(x) = x^k - sum c[j]x^j
ll kitamasa(vl dp, vl c, ll N) {
    int k = c.size();
    vl f(k+1);
    f[k] = 1;
    for(int i=0; i<k; i++) f[i] = (MOD - c[i]) % MOD;
    Poly<ll> mod_poly(f);

    Poly<ll> result(1), base(vl{0, 1}); // result = x^0 = 1, base = x^1
    while(N) {
        if(N & 1) result = result.mulmod(base).divmod(mod_poly).second;
        base = base.mulmod(base).divmod(mod_poly).second;
        N >>= 1;
    }

    ll ans = 0;
    for(int i=0; i<k; i++) ans = (ans + result[i] * dp[i]) % MOD;
    return ans;
}
