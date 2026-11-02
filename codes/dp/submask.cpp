// Enumerate every submask of 'mask' (including mask itself and 0).
// Time: O(3^n) total over all 2^n masks of an n-bit universe
// (each bit is 0 in mask, or 1-and-in-sub, or 1-and-not-in-sub: 3 choices per bit)
for(int sub = mask; ; sub = (sub-1) & mask) {
    // ... use sub ...
    if(sub == 0) break;
}

// usage example: sum[mask] = sum of val[sub] over every submask sub of mask
ll val[1<<20], sum[1<<20];
void submask_sum(int n) {
    for(int mask=0; mask<(1<<n); mask++) {
        for(int sub = mask; ; sub = (sub-1) & mask) {
            sum[mask] += val[sub];
            if(sub == 0) break;
        }
    }
}
