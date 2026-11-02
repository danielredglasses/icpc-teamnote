void calc_lps() {
    int j=2, len = 0;
    lps[1] = 0;
    while(j <= m) {
        if(s2[j] == s2[len+1]) lps[j++] = ++len;
        else {
            if(len) len = lps[len];
            else lps[j++] = 0;
        }
    }
}

void SolveProblem() {
    cin >> s1; 
    n = s1.size(); s1 = " " + s1;
    cin >> s2;
    m = s2.size(); s2 = " " + s2;
    
    calc_lps();
    
    for(int i=1; i<=n; i++) {
        while(1) {
            if(j+1 <= m && s1[i] == s2[j+1]) {
                j++;
                break;
            }
            else {
                if(j) j = lps[j];
                else break;
            }
        }
    }
}