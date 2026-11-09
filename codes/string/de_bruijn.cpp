// De Bruijn sequence: cyclic string of length k^n containing every length-n string over [0, k-1]. Time complexity: O(k^n)
int res[10000000]; // >= k^n
int aux[10000000]; // >= k*n

// usage: de_bruijn(k, n) fills res[0..k^n-1] and returns k^n
int de_bruijn(int k, int n) {
    if(k == 1) {
        res[0] = 0;
        return 1;
    }
    for(int i=0; i<k*n; i++) aux[i] = 0;
    int sz = 0;
    function<void(int, int)> db = [&](int t, int p) {
        if(t > n) {
            if(n % p == 0) for(int i=1; i<=p; i++) res[sz++] = aux[i];
        }
        else {
            aux[t] = aux[t-p];
            db(t+1, p);
            for(int i=aux[t-p]+1; i<k; i++) {
                aux[t] = i;
                db(t+1, t);
            }
        }
    };
    db(1, 1);
    return sz;
}
