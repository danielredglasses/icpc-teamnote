pll p[100005];
ll sqr(ll x) { return x * x; }

// usage: fill p[1..n] (n >= 2) and sort(p+1, p+n+1) (sorts by x then y), then
ll closest_pair(int n, pii &ans) {
    set<tuple<ll, ll, int>> s; // (y, x, idx) of points 
    ll d = LLONG_MAX;
    for(int i=1, l=1; i<=n; i++) {
        ll rad = (ll) sqrtl((ld) d) + 1;
        while(p[i].first - p[l].first > rad) s.erase({p[l].second, p[l].first, l}), l++;
        for(auto it=s.lower_bound({p[i].second-rad, LLONG_MIN, 0}); it!=s.end() && get<0>(*it)<=p[i].second+rad; it++) {
            ll nd = sqr(p[i].first - get<1>(*it)) + sqr(p[i].second - get<0>(*it));
            if(nd < d) { 
                d = nd; 
                ans = {i, get<2>(*it)}; 
            }
        }
        s.insert({p[i].second, p[i].first, i});
    }
    return d;
}
