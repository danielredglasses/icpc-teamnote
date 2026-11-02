// Time: O((N+Q) log N) calls to apply_event/reset/satisfied combined,
// each O(log N) rounds.
// Use when: Q offline queries each want the smallest time t in [1,N] with
// a monotonic (once true, stays true) condition satisfied(q) after events
// 1..t are applied in order, but applying/undoing events isn't cheap to
// jump to an arbitrary t directly (e.g. DSU unions) - so binary-searching
// each query independently (replaying from scratch each step) is too slow.
// Batches all queries' binary search steps by round instead: each round
// does one O(N) pass.
int lo_[100005], hi_[100005], mid_[100005], pbs_ans[100005];
vi bucket_[100005];

// apply_event(t): apply the t-th event (1-indexed).
// reset(): undo all events, back to t=0.
// satisfied(q): true iff query q's condition holds after events
// 1..mid_[q] are applied.
// after return, pbs_ans[q] = smallest t with satisfied(q) true
// (N+1 if never satisfied).
void parallel_binary_search(int Q, int N, function<void(int)> apply_event,
                             function<void()> reset, function<bool(int)> satisfied) {
    for(int i=1; i<=Q; i++) { lo_[i] = 1; hi_[i] = N+1; }
    while(true) {
        bool changed = false;
        for(int t=0; t<=N; t++) bucket_[t].clear();
        for(int i=1; i<=Q; i++) if(lo_[i] < hi_[i]) {
            changed = true;
            mid_[i] = (lo_[i]+hi_[i])/2;
            bucket_[mid_[i]].push_back(i);
        }
        if(!changed) break;
        reset();
        for(int t=1; t<=N; t++) {
            apply_event(t);
            for(int q : bucket_[t]) {
                if(satisfied(q)) hi_[q] = mid_[q];
                else lo_[q] = mid_[q]+1;
            }
        }
    }
    for(int i=1; i<=Q; i++) pbs_ans[i] = lo_[i];
}
