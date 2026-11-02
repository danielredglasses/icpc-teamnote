struct XorBasis {
    static const int B = 62;
    ll basis[B] = {0}; int cnt = 0;
    bool insert(ll x) {
        for(int i=B-1; i>=0; i--) if((x>>i)&1) {
            if(!basis[i]) { 
                basis[i] = x; 
                cnt++; 
                return true; 
            }
            x ^= basis[i];
        }
        return false;
    }
    ll max_xor(ll x) { // x와 xor 했을 때 만들 수 있는 최댓값
        for(int i=B-1; i>=0; i--) if((x^basis[i]) > x) x ^= basis[i];
        return x;
    }
    ll min_xor(ll x) { // x와 xor 했을 때 만들 수 있는 최솟값
        for(int i=B-1; i>=0; i--) if(basis[i] && (x^basis[i]) < x) x ^= basis[i];
        return x;
    }
    bool can_represent(ll x) {
        for(int i=B-1; i>=0; i--) if((x>>i)&1) {
            if(!basis[i]) return false;
            x ^= basis[i];
        }
        return true;
    }
};
