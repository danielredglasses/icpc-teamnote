// FWT: OR / AND / XOR subset convolution mod MOD. a.size() must be a power of 2.
// Time: O(n log n)
const ll INV2 = (MOD+1) / 2;

void fwt_or(vl &a, bool invert) {
    int n = a.size();
    for(int len=1; len<n; len<<=1)
        for(int i=0; i<n; i+=len*2)
            for(int j=i; j<i+len; j++) {
                if(!invert) a[j+len] = (a[j+len] + a[j]) % MOD;
                else a[j+len] = (a[j+len] - a[j] + MOD) % MOD;
            }
}

void fwt_and(vl &a, bool invert) {
    int n = a.size();
    for(int len=1; len<n; len<<=1)
        for(int i=0; i<n; i+=len*2)
            for(int j=i; j<i+len; j++) {
                if(!invert) a[j] = (a[j] + a[j+len]) % MOD;
                else a[j] = (a[j] - a[j+len] + MOD) % MOD;
            }
}

void fwt_xor(vl &a, bool invert) {
    int n = a.size();
    for(int len=1; len<n; len<<=1)
        for(int i=0; i<n; i+=len*2)
            for(int j=i; j<i+len; j++) {
                ll u = a[j], v = a[j+len];
                a[j] = (u + v) % MOD;
                a[j+len] = (u - v + MOD) % MOD;
                if(invert) { a[j] = a[j] * INV2 % MOD; a[j+len] = a[j+len] * INV2 % MOD; }
            }
}

// usage: zero-pad a, b to the same power-of-2 length, then e.g. for XOR convolution:
// fwt_xor(a, false); fwt_xor(b, false);
// for(int i=0; i<n; i++) a[i] = a[i]*b[i] % MOD; fwt_xor(a, true);
