ll pow_mod(ll a, ll b, ll p) {
    a %= p;
    ll r = 1;
    while(b) {
        if(b & 1) r = r * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return r;
}

// solve x^2 = a (mod p); p must be an odd prime; returns -1 if a is a non-residue
ll discrete_sqrt(ll a, ll p) {
    if(a == 0) return 0;
    if(pow_mod(a, (p-1)/2, p) != 1) return -1;
    if(p % 4 == 3) return pow_mod(a, (p+1)/4, p);

    ll s = p - 1, n = 2, r = 0, m;
    while(~s & 1) { r++; s >>= 1; }
    while(pow_mod(n, (p-1)/2, p) != p-1) n++;

    ll x = pow_mod(a, (s+1)/2, p), b = pow_mod(a, s, p), g = pow_mod(n, s, p);
    for(;; r=m) {
        ll t = b;
        for(m=0; m<r && t!=1; m++) t = t * t % p;
        if(!m) return x;
        ll gs = pow_mod(g, 1LL << (r-m-1), p);
        g = gs * gs % p;
        x = x * gs % p;
        b = b * g % p;
    }
}
