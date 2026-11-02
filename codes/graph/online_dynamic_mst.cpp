void SolveProblem() {
    cin >> n >> q;
    
    S.clear();
    S.init(n*2+q);
    for(int i=1; i<=n; i++) {
        edges[i].clear();
        S.update_node(i, -1e18);
    }
    
    result = 0;
    for(int i=2; i<=n; i++) {
        int p; ll d; cin >> p >> d; p++;
        edges[p].push_back({i, d});
        result += d;
    }
    
    m = n;
    dfs(1, -1);
    
    while(q--) {
        int a, b; ll d; cin >> a >> b >> d; a++; b++;
        
        pll mx = S.query(a, b);
        if(mx.first > d) {
            int cur = mx.second;
            int x, y; tie(x, y) = connected[cur];
            
            result += d - mx.first;
            S.cut(mx.second, connected[cur].first);
            S.cut(mx.second, connected[cur].second);
            
            ++m;
            S.update_node(m, d);
            connected[m] = {a, b};
            
            S.reroot(m); S.reroot(a);
            S.link(m, a);
            
            S.reroot(m); S.reroot(b);
            S.link(m, b);
        }
    }
    
    cout << result << "\n";
}