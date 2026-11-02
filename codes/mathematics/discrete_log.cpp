#include <ext/pb_ds/assoc_container.hpp>

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

// smallest x >= 0 with a^x = b (mod p); p must be prime
ll discrete_log(ll a, ll b, ll p) {
    __gnu_pbds::gp_hash_table<ll, __gnu_pbds::null_type> st;
    ll t = (ll) ceil(sqrt((double) p)), k = 1;
    for(int i=0; i<t; i++) { st.insert(k); k = k * a % p; }

    ll inv = pow_mod(k, p-2, p);
    for(int i=0, k=1; i<t; i++, k=k*inv%p) {
        ll x = b * k % p;
        if(st.find(x) == st.end()) continue;
        for(int j=0, k=1; j<t; j++, k=k*a%p) if(k == x) return i * t + j;
    }
    return -1;
}
