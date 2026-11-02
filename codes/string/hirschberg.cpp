// O(n+m) space
string a, b;
int n, m;

int dp1[7005], dp2[7005];
string result = "";

void DnC(int l, int r, int s, int e) {
    if(l == r) {
        for(int i=s; i<=e; i++) if(a[l] == b[i]) {
            result += a[l];
            break;
        }
        return;
    }
    
    int mid = (l+r)/2;
    
    for(int j=s-1; j<=e; j++) dp1[j] = 0;
    for(int i=l; i<=mid; i++) {
        for(int j=e; j>=s; j--) {
            if(a[i] == b[j]) dp1[j] = max(dp1[j], dp1[j-1] + 1);
        }
        for(int j=s+1; j<=e; j++) dp1[j] = max(dp1[j], dp1[j-1]);
    }
    
    for(int j=s; j<=e+1; j++) dp2[j] = 0;
    for(int i=r; i>=mid+1; i--) {
        for(int j=s; j<=e; j++) {
            if(a[i] == b[j]) dp2[j] = max(dp2[j], dp2[j+1] + 1);
        }
        for(int j=e-1; j>=s; j--) dp2[j] = max(dp2[j], dp2[j+1]);
    }
    
    int nx = -1, mx = -1;
    for(int i=s-1; i<=e; i++) {
        if(mx < dp1[i] + dp2[i+1]) {
            mx = dp1[i] + dp2[i+1];
            nx = i;
        }
    }
    
    DnC(l, mid, s, nx); DnC(mid+1, r, nx+1, e);
}

void SolveProblem() {
    cin >> a >> b;
    n = a.size(); a = " " + a;
    m = b.size(); b = " " + b;
    
    DnC(1, n, 1, m);
    
    cout << result.size() << "\n";
    cout << result << "\n";
}