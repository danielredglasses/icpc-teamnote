int n; cin >> n;
for(int i=1; i<=n; i++) cin >> arr[i];

priority_queue<ll> pq; pq.push(arr[1]);
ll x_shift = 0, result = 0;
for(int i=2; i<=n; i++) {
    x_shift++;
    ll x_min = pq.top() + x_shift;
    if(arr[i] <= x_min) {
        result += x_min - arr[i];
        pq.pop(); pq.push(arr[i] - x_shift);
    }
    pq.push(arr[i] - x_shift);
}

cout << result << "\n";