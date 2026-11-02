// sum_{i=0}^n [(a*i+b)/c]
ll floor_sum(ll a, ll b, ll c, ll n) {
    if(!a) return b / c * (n+1);

    if(a >= c || b >= c) return n * (n+1) / 2 * (a / c) + (n+1) * (b / c) + floor_sum(a%c, b%c, c, n);

    ll m = (a * n + b) / c;
    return m * n - floor_sum(c, c-b-1, a, m-1);
}