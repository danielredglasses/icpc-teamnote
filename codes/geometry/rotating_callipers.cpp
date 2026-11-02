pll operator - (const pll &a, const pll &b) {
    return pll(a.first - b.first, a.second - b.second);
}

ll dist(pll a, pll b) { 
    ll dx = a.first - b.first, dy = a.second - b.second; 
    return dx*dx + dy*dy; 
}

// usage: hull in CCW order;
ll rotating_callipers(vector<pll> &convex, pii &ans) {
    int m = convex.size();
    if(m == 1) { 
        ans = {0, 0}; 
        return 0; 
    }
    
    int idx1 = 0, idx2 = 1; ll maxdist = 0;
    for(int i=0; i<m*2; i++) {
        ll d = dist(convex[idx1], convex[idx2]);
        if(d > maxdist) { 
            maxdist = d; 
            ans = {idx1, idx2}; 
        }
        int nx1 = (idx1+1)%m, nx2 = (idx2+1)%m;
        pll diff1 = convex[idx1] - convex[nx1], diff2 = convex[idx2] - convex[nx2];
        if(ccw(diff1, pll(0, 0), diff2) < 0) idx2 = nx2;
        else idx1 = nx1;
    }
    return maxdist;
}