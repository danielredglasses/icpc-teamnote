ll gcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0) {
        x = 1; y = 0;
        return a;
    }
    ll x1, y1;
    ll d = gcd(b, a%b, x1, y1);
    x = y1; y = x1 - y1 * (a/b);
    return d;
}

ll find_rem(i128 a, i128 b) {
    return a%b >= 0 ? a%b : a%b + b;
}

pll crt(ll a, ll b, ll r1, ll r2) { // r1 (mod a) & r2 (mod b)
    ll x0, y0;
    ll g = gcd(a, b, x0, y0);
    if((r2 - r1) % g != 0) return {0, 0};
    i128 mod = (i128) a / g * b;
    i128 rem = find_rem(((i128) r1 * (b/g) % mod) * y0, mod) + find_rem(((i128) r2 * (a/g) % mod) * x0, mod);
    rem = (rem + mod) % mod;
    return {mod, rem};
}