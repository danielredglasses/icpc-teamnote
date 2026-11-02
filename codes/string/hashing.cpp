const ll MOD1 = 1e9 + 7, MOD2 = 998244353, p1 = 19192734, p2 = 603820;
const ll inv_p1 = 90700002, inv_p2 = 752581546;
ll pw1[500005], pw2[500005], h1[500005], h2[500005];

void precompute_pow() {
    pw1[0] = pw2[0] = 1;
    for(int i=1; i<500005; i++) { pw1[i] = pw1[i-1] * p1 % MOD1; pw2[i] = pw2[i-1] * p2 % MOD2; }
}
void build(string &s) {
    int n = (int) s.size()-1;
    h1[0] = h2[0] = 0;
    for(int i=1; i<=n; i++) { h1[i] = (h1[i-1] * p1 + s[i]) % MOD1; h2[i] = (h2[i-1] * p2 + s[i]) % MOD2; }
}
pll get_hash(int l, int r) {
    return {((h1[r] - h1[l-1] * pw1[r-l+1]) % MOD1 + MOD1) % MOD1, ((h2[r] - h2[l-1] * pw2[r-l+1]) % MOD2 + MOD2) % MOD2};
}

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const { return std::hash<T1>{}(p.first) ^ std::hash<T2>{}(p.second); }
};
