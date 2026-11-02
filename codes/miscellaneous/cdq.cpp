ll cdq(int l, int r) {
    if(l == r) return 0;
    
    int mid = (l+r)/2;
    ll curresult = cdq(l, mid) + cdq(mid+1, r);
    
    int idx_l = l, idx_r = mid+1, idx_tmp = l;
    while(idx_l <= mid && idx_r <= r) {
        if(idx[idx_l][2] <= idx[idx_r][2]) {
            S.update(idx[idx_l][3], 1);
            
            for(int j=1; j<=3; j++) tmp[idx_tmp][j] = idx[idx_l][j];
            idx_tmp++; idx_l++;
        }
        else {
            curresult += S.find_sum(idx[idx_r][3]);
            
            for(int j=1; j<=3; j++) tmp[idx_tmp][j] = idx[idx_r][j];
            idx_tmp++; idx_r++;
        }
    }
    
    int idx_l1 = idx_l, idx_r1 = idx_r;
    while(idx_l1 <= mid) {
        for(int j=1; j<=3; j++) tmp[idx_tmp][j] = idx[idx_l1][j];
        idx_tmp++; idx_l1++;
    }
    while(idx_r1 <= r) {
        curresult += S.find_sum(idx[idx_r1][3]);
        
        for(int j=1; j<=3; j++) tmp[idx_tmp][j] = idx[idx_r1][j];
        idx_tmp++; idx_r1++;
    }
    
    for(int i=l; i<idx_l; i++) S.update(idx[i][3], -1);
    for(int i=l; i<=r; i++) for(int j=1; j<=3; j++) idx[i][j] = tmp[i][j];
    
    return curresult;
}