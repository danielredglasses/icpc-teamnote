struct query {
    int start, end, num;
    bool operator< (const query& other) const {
        if(start / sqrtN == other.start / sqrtN) return end < other.end;
        return start / sqrtN < other.start / sqrtN;
    }
};
ll cur_ans = 0;
void add(int idx) { /* fill in per-problem */ }
void remove(int idx) { /* fill in per-problem */ }
void solve_mo(vector<query> &queries, vl &ans) {
    sort(all(queries));
    int cur_l = 1, cur_r = 0;
    for(query &q : queries) {
        while(cur_r < q.end) add(++cur_r);
        while(cur_l > q.start) add(--cur_l);
        while(cur_r > q.end) remove(cur_r--);
        while(cur_l < q.start) remove(cur_l++);
        ans[q.num] = cur_ans;
    }
}
