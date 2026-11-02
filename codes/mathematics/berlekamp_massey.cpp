// Time: berlekamp_massey O(n^2); guess_nth_term O(n^2 + k^2 log n)
// (k = recurrence order found);
// get_min_poly/det O(n*(n+|M|)) (|M| = number of nonzero matrix entries)
ll ipow(ll x, ll p){
    ll ret = 1, piv = x;
    while(p){
        if(p & 1) ret = ret * piv % MOD;
        piv = piv * piv % MOD;
        p >>= 1;
    }
    return ret;
}
vi berlekamp_massey(vi x){
    vi ls, cur;
    int lf, lastd;
    for(int i=0; i<x.size(); i++){
        ll t = 0;
        for(int j=0; j<cur.size(); j++){
            t = (t + 1ll * x[i-j-1] * cur[j]) % MOD;
        }
        if((t - x[i]) % MOD == 0) continue;
        if(cur.empty()){
            cur.resize(i+1);
            lf = i;
            lastd = (t - x[i]) % MOD;
            continue;
        }
        ll k = -(x[i] - t) * ipow(lastd, MOD-2) % MOD;
        vi c(i-lf-1);
        c.push_back(k);
        for(auto &j : ls) c.push_back(-j * k % MOD);
        if(c.size() < cur.size()) c.resize(cur.size());
        for(int j=0; j<cur.size(); j++){
            c[j] = (c[j] + cur[j]) % MOD;
        }
        if(i-lf+(int)ls.size()>=(int)cur.size()){
            tie(ls, lf, lastd) = make_tuple(cur, i, (t - x[i]) % MOD);
        }
        cur = c;
    }
    for(auto &i : cur) i = (i%MOD + MOD) % MOD;
    return cur;
}
int get_nth(vi rec, vi dp, ll n){
    int m = rec.size();
    vi s(m), t(m);
    s[0] = 1;
    if(m != 1) t[1] = 1;
    else t[0] = rec[0];
    auto mul = [&rec](vi v, vi w){
        int m = v.size();
        vi t(2 * m);
        for(int j=0; j<m; j++){
            for(int k=0; k<m; k++){
                t[j+k] += 1ll * v[j] * w[k] % MOD;
                if(t[j+k] >= MOD) t[j+k] -= MOD;
            }
        }
        for(int j=2*m-1; j>=m; j--){
            for(int k=1; k<=m; k++){
                t[j-k] += 1ll * t[j] * rec[k-1] % MOD;
                if(t[j-k] >= MOD) t[j-k] -= MOD;
            }
        }
        t.resize(m);
        return t;
    };
    while(n){
        if(n & 1) s = mul(s, t);
        t = mul(t, t);
        n >>= 1;
    }
    ll ret = 0;
    for(int i=0; i<m; i++) ret += 1ll * s[i] * dp[i] % MOD;
    return ret % MOD;
}
int guess_nth_term(vi x, ll n){
    if(n < x.size()) return x[n];
    vi v = berlekamp_massey(x);
    if(v.empty()) return 0;
    return get_nth(v, x, n);
}
struct elem{int x, y, v;}; // A_(x, y) <- v, 0-based. no duplicate please..
vi get_min_poly(int n, vector<elem> M){
    // smallest poly P such that A^i = sum_{j < i} {A^j \times P_j}
    vi rnd1, rnd2;
    random_device rd;
    mt19937 gen(rd());
    auto randint = [&gen](int lb, int ub){
        return uniform_int_distribution<int>(lb, ub)(gen);
    };
    for(int i=0; i<n; i++){
        rnd1.push_back(randint(1, MOD-1));
        rnd2.push_back(randint(1, MOD-1));
    }
    vi gobs;
    for(int i=0; i<n*2+2; i++){
        int tmp = 0;
        for(int j=0; j<n; j++){
            tmp += 1ll * rnd2[j] * rnd1[j] % MOD;
            if(tmp >= MOD) tmp -= MOD;
        }
        gobs.push_back(tmp);
        vi nxt(n);
        for(auto &i : M){
            nxt[i.x] += 1ll * i.v * rnd1[i.y] % MOD;
            if(nxt[i.x] >= MOD) nxt[i.x] -= MOD;
        }
        rnd1 = nxt;
    }
    auto sol = berlekamp_massey(gobs);
    reverse(all(sol));
    return sol;
}
ll det(int n, vector<elem> M){
    vi rnd;
    random_device rd;
    mt19937 gen(rd());
    auto randint = [&gen](int lb, int ub){
        return uniform_int_distribution<int>(lb, ub)(gen);
    };
    for(int i=0; i<n; i++) rnd.push_back(randint(1, MOD-1));
    for(auto &i : M){
        i.v = 1ll * i.v * rnd[i.y] % MOD;
    }
    auto sol = get_min_poly(n, M)[0];
    if(n % 2 == 0) sol = MOD - sol;
    for(auto &i : rnd) sol = 1ll * sol * ipow(i, MOD-2) % MOD;
    return sol;
}