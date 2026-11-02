// result[i] = min_{j=i-m+1,...,i} arr[j]
deque<pii> dq;
for(int i=1; i<=n; i++) {
    while(!dq.empty() && dq.front().second < i-m+1) dq.pop_front();
    while(!dq.empty() && dq.back().first >= arr[i]) dq.pop_back();
    dq.push_back({arr[i], i});

    result[i] = dq.front().first;
}