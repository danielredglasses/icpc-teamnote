fact[0] = fact_inv[0] = 1;
fact[1] = inv[1] = fact_inv[1] = 1;
for(int i=2; i<3005; i++) {
    fact[i] = fact[i-1] * i % MOD;
    inv[i] = (MOD - (MOD / i) * inv[MOD % i] % MOD) % MOD;
    fact_inv[i] = fact_inv[i-1] * inv[i] % MOD;
}