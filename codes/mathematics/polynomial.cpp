// evalmod (multi-point) is O(n log^2 n);
template<typename T>
struct Poly {
    static T MOD, ROOT, ROOT_INV;

    static void set_mod(T mod) {
        MOD = mod;
        ROOT = find_primitive_root(mod);
        ROOT_INV = powers(ROOT, mod-2);
    }

    static T powers(T a, T b) {
        if(b == 0) return 1;
        T res = powers(a, b/2);
        res = (ll) res * res % MOD;
        if(b%2 == 1) res = (ll) res * a % MOD;
        return res;
    }
    static int find_primitive_root(ll p) {
        if(p <= 1) return -1;
        for(ll i=2; i*i<=p; i++) if(p%i == 0) return -1;
        
        ll phi = p-1;
        
        ll tmp = phi; vl factors;
        for(ll i=2; i*i<=tmp; i++) if(tmp%i == 0) {
            factors.push_back(i);
            while(tmp%i == 0) tmp /= i; 
        }
        if(tmp > 1) factors.push_back(tmp);
        
        for(ll res=2; res<=p; res++) {
            bool is_primitive_root = true;
            for(ll factor : factors) if(powers(res, phi/factor) == 1) {
                is_primitive_root = false;
                break;
            }
            if(is_primitive_root) return res;
        }

        return -1;
    }

    vector<T> coef;

    Poly(const vector<T>& c) : coef(c) { normalize(); }
    Poly(T c) : coef(1, c) { normalize(); }
    Poly() : coef{ } { }

    int deg() const { return coef.size(); }
    int size() const { return deg(); }

    T operator [] (int i) const { return i < deg() ? coef[i] : 0; }
    T& operator [] (int i) {
        if(i >= deg()) coef.resize(i+1, 0);
        return coef[i];
    }

    Poly& normalize() {
        while(deg() >= 1 && coef.back() == 0) coef.pop_back();
        return *this;
    }
    Poly& modular() {
        for(auto& x : coef) {
            x %= MOD;
            if(x < 0) x += MOD;
        }
        normalize();
        return *this;
    }
    Poly& resize(int sz) {
        coef.resize(sz, 0);
        return *this;
    }
    Poly reverse() const {
        vector<T> rev(rall(coef));
        return Poly(rev);
    }

    Poly operator + (const Poly& other) const {
        int sz = max(deg(), other.deg());
        vector<T> res(sz, 0);
        for(int i=0; i<sz; i++) res[i] = (*this)[i] + other[i];
        return Poly(res);
    }
    Poly& operator += (const Poly& other) { return *this = *this + other; }
    Poly addmod(const Poly& other) const { return (*this + other).modular(); }

    Poly operator - (const Poly& other) const {
        int sz = max(deg(), other.deg());
        vector<T> res(sz, 0);
        for(int i=0; i<sz; i++) res[i] = (*this)[i] - other[i];
        return Poly(res);
    }
    Poly& operator -= (const Poly& other) { return *this = *this - other; }
    Poly submod(const Poly& other) const { return (*this - other).modular(); }

    // long double FFT: exact only while result values stay well below
    // ~1e12; use mulmod otherwise
    Poly operator * (const Poly& other) const {
        int sz = 1;
        while(sz < deg() + other.deg()) sz <<= 1;
        
        vector<cpx> fa(sz, 0), fb(sz, 0);
        for(int i=0; i<deg(); i++) fa[i] = coef[i];
        for(int i=0; i<other.deg(); i++) fb[i] = other.coef[i];
        
        fft(fa, false); fft(fb, false);
        
        for(int i=0; i<sz; i++) fa[i] *= fb[i];
        fft(fa, true);
        
        vector<T> res(sz);
        for(int i=0; i<sz; i++) res[i] = round(fa[i].real());
        return Poly(res);
    }
    Poly& operator *= (const Poly& other) { return *this = *this * other; }

    static void fft(vector<cpx>& a, bool invert) {
        int n = a.size();
        for(int i=1, j=0; i<n; i++) {
            int bit = n >> 1;
            while(j & bit) { j -= bit; bit >>= 1; }
            j += bit;
            if(i < j) swap(a[i], a[j]);
        }
        
        for(int len=2; len<=n; len<<=1) {
            ld ang = 2 * M_PI / len * (invert ? -1 : 1);
            cpx cw(cos(ang), sin(ang));
            for(int i=0; i<n; i+=len) {
                cpx w(1);
                for(int j=0; j<len/2; j++) {
                    cpx u = a[i+j], v = a[i+j+len/2] * w;
                    a[i+j] = u + v;
                    a[i+j+len/2] = u - v;
                    w *= cw;
                }
            }
        }
        
        if(invert) for(int i=0; i<n; i++) a[i] /= n;
    }

    void ntt(vector<T>& a, bool invert) const {
        int n = a.size();
        for(int i=1, j=0; i<n; i++) {
            int bit = n >> 1;
            while(j & bit) { j -= bit; bit >>= 1; }
            j += bit;
            if(i < j) swap(a[i], a[j]);
        }
        
        vector<T> roots(n);
        roots[0] = 1;
        T cw = powers(invert ? ROOT_INV : ROOT, (MOD-1)/n);
        for(int i=1; i<n; i++) roots[i] = (ll) roots[i-1] * cw % MOD;
        
        for(int len=2; len<=n; len<<=1) {
            int step = n / len;
            for(int i=0; i<n; i+=len) {
                for(int j=0; j<len/2; j++) {
                    T u = a[i+j], v = (ll) a[i+j+len/2] * roots[j*step] % MOD;
                    a[i+j] = u+v < MOD ? u+v : u+v-MOD;
                    a[i+j+len/2] = u-v >= 0 ? u-v : u-v+MOD;
                }
            }
        }
        
        if(invert) {
            T inv_n = powers(n, MOD-2);
            for(auto& x : a) x = (ll) x * inv_n % MOD;
        }
    }

    Poly mulmod(const Poly& other) const {
        int sz = 1;
        while(sz < deg() + other.deg()) sz <<= 1;
        
        vector<T> a(sz, 0), b(sz, 0);
        for(int i=0; i<deg(); i++) a[i] = coef[i] % MOD;
        for(int i=0; i<other.deg(); i++) b[i] = other.coef[i] % MOD;

        ntt(a, false); ntt(b, false);
        for(int i=0; i<sz; i++) a[i] = (ll) a[i] * b[i] % MOD;
        ntt(a, true);

        return Poly(a);
    }

    Poly invmod(int high_deg) const {
        assert((*this)[0] != 0);
        
        Poly b(powers((*this)[0], MOD-2));

        while(b.deg() < high_deg) {
            int m = min(b.deg() * 2, high_deg);

            Poly a = *this; a.resize(m);
            b.resize(m);

            b = b.mulmod(Poly(2).submod(a.mulmod(b)));
            b.resize(m);
        }

        return b.resize(high_deg).normalize();
    }

    pair<Poly, Poly> divmod(const Poly& other) const {
        if(deg() < other.deg()) return {Poly(0), *this};

        int q_deg = deg() - other.deg() + 1; 

        Poly rev_inv = other.reverse().invmod(q_deg);
        Poly q = this->reverse().mulmod(rev_inv);
        q = q.resize(q_deg).reverse().normalize();
        Poly r = this->submod(other.mulmod(q)).normalize();

        return {q, r};
    }

    Poly diffmod() const {
        if(deg() <= 1) return Poly(0);
        
        vector<T> res(deg()-1, 0);
        for(int i=1; i<deg(); i++) res[i-1] = (ll) coef[i] * i % MOD;
        
        return Poly(res);
    }

    Poly intmod() const {
        vector<T> inv(deg()+1, 0);
        inv[1] = 1;
        for(int i=2; i<=deg(); i++) inv[i] = (MOD - MOD/i) * inv[MOD%i] % MOD;

        vector<T> res(deg()+1, 0);
        for(int i=0; i<deg(); i++) res[i+1] = (ll) coef[i] * inv[i+1] % MOD;
        
        return Poly(res);
    }

    Poly logmod(int high_deg) const {
        assert((*this)[0] == 1);

        return diffmod().mulmod(invmod(high_deg)).resize(high_deg - 1).intmod().resize(high_deg).normalize();
    }

    Poly expmod(int high_deg) const {
        assert((*this)[0] == 0);

        Poly b(1), b_inv(1);
        while(b.deg() < high_deg) {
            int m = min(b.deg() * 2, high_deg);

            Poly f = *this; f.resize(m);
            b = b.mulmod(Poly(1).addmod(f.submod(b.logmod(m)))).resize(m);
        }
        return b.resize(high_deg).normalize();
    }

    Poly sqrtmod(int high_deg) const {
        assert((*this)[0] == 1);

        T inv2 = powers(2, MOD-2);
        Poly b(1);
        while(b.deg() < high_deg) {
            int m = min(b.deg()*2, high_deg);

            Poly f = *this; f.resize(m);
            Poly sum = b.addmod(f.mulmod(b.invmod(m))).resize(m);
            for(T &x : sum.coef) x = (ll) x * inv2 % MOD;
            b = sum.resize(m);
        }
        return b.resize(high_deg).normalize();
    }

    Poly powmod(ll k, int high_deg) const {
        assert((*this)[0] == 1);

        Poly l = logmod(high_deg);
        T kk = ((k % MOD) + MOD) % MOD;
        for(T &x : l.coef) x = (ll) x * kk % MOD;
        return l.resize(high_deg).expmod(high_deg);
    }

    T evalmod(T x) const {
        T result = 0, xn = 1;
        for(int i=0; i<deg(); i++) {
            result = (result + (ll) xn * coef[i]) % MOD;
            xn = (ll) xn * x % MOD;
        }
        return result;
    }
    
    vector<T> evalmod(const vector<T>& x) const {
        int n = x.size();
        vector<Poly> subprod(n*4);

        function<void(int, int, int)> build = [&](int index, int l, int r) {
            if(l == r) {
                subprod[index] = Poly({(MOD - x[l]) % MOD, 1});
                return;
            }
            int mid = (l+r)/2;
            build(index*2, l, mid); build(index*2+1, mid+1, r);
            subprod[index] = subprod[index*2].mulmod(subprod[index*2+1]);
        };
        build(1, 0, n-1);

        vector<T> result(n);
        function<void(int, int, int, const Poly&)> eval = [&](int index, int l, int r, const Poly& cur) {
            if(l == r) {
                result[l] = cur.evalmod(x[l]);
                return;
            }
            int mid = (l+r)/2;
            eval(index*2, l, mid, cur.divmod(subprod[index*2]).second);
            eval(index*2+1, mid+1, r, cur.divmod(subprod[index*2+1]).second);
        };
        eval(1, 0, n-1, *this);

        return result;
    }
    
    // (x_i, y_i)를 전부 지나는 n차 다항식을 반환
    static Poly interpolate(const vector<T>& x, const vector<T>& y) {
        int n = x.size();
        vector<Poly> subprod(n*4);

        function<void(int, int, int)> build = [&](int index, int l, int r) {
            if(l == r) {
                subprod[index] = Poly({(MOD - x[l]) % MOD, 1});
                return;
            }
            int mid = (l+r)/2;
            build(index*2, l, mid); build(index*2+1, mid+1, r);
            subprod[index] = subprod[index*2].mulmod(subprod[index*2+1]);
        };
        build(1, 0, n-1);

        vector<T> denom = subprod[1].diffmod().evalmod(x);
        vector<T> c(n);
        for(int i=0; i<n; i++) c[i] = (ll) y[i] * powers(denom[i], MOD-2) % MOD;

        function<Poly(int, int, int)> solve = [&](int index, int l, int r) -> Poly {
            if(l == r) return Poly(c[l]);
            int mid = (l+r)/2;
            return solve(index*2, l, mid).mulmod(subprod[index*2+1]).addmod(solve(index*2+1, mid+1, r).mulmod(subprod[index*2]));
        };
        return solve(1, 0, n-1);
    }

    // P(x)/Q(x)를 거듭제곱수로 전개했을 때, n번째 계수 반환
    static T bostan_mori(Poly P, Poly Q, ll n) {
        while(n > 0) {
            Poly Q_neg = Q;
            for(int i=1; i<Q_neg.deg(); i+=2) Q_neg[i] = (MOD - Q_neg[i]) % MOD;
            Poly new_P = P.mulmod(Q_neg), new_Q = Q.mulmod(Q_neg);

            int parity = n & 1;
            vector<T> Pc, Qc;
            for(int i=parity; i<new_P.deg(); i+=2) Pc.push_back(new_P[i]);
            for(int i=0; i<new_Q.deg(); i+=2) Qc.push_back(new_Q[i]);
            P = Poly(Pc); Q = Poly(Qc);
            n >>= 1;
        }
        return (ll) P[0] * powers(Q[0], MOD-2) % MOD;
    }
};

template<typename T> T Poly<T>::MOD = 0;
template<typename T> T Poly<T>::ROOT = 0;
template<typename T> T Poly<T>::ROOT_INV = 0;

/*
Poly<ll>::set_mod(998244353);
Poly<ll> a;
for(int i=0; i<n; i++) cin >> a[i];
*/