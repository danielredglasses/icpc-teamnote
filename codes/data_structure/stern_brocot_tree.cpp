// Stern-Brocot tree search over fractions p/q (0 <= p, 1 <= q, p, q <= N)
bool f(ll p, ll q) { return p * p >= 2 * q * q; } // monotone in p/q (false -> true)

pair<pll, pll> stern_brocot(ll N) {
    pll lo = {0, 1}, hi = {1, 0};
    while(lo.first + hi.first <= N && lo.second + hi.second <= N) {
        for(int t=0; t<2; t++) {
            pll &a = t ? hi : lo, &b = t ? lo : hi;
            auto ok = [&](ll k) {
                ll p = a.first + k * b.first, q = a.second + k * b.second;
                return p <= N && q <= N && f(p, q) == (bool) t;
            };
            ll k = 0, step = 1;
            while(ok(k + step)) k += step, step *= 2;
            for(; step; step/=2) if(ok(k + step)) k += step;
            a.first += k * b.first, a.second += k * b.second;
        }
    }
    return {lo, hi};
}
