// cus_like[i] = customer i's resources in preference order
// (1-indexed, most preferred first)
// res_pref[r][i] = resource r's rank for customer i (lower = better)
// Time: O(n^2)
int n;
vi cus_like[1005];
int res_pref[1005][1005], cap[1005];
priority_queue<pii> res_to_cus[1005];
int idx[1005], cus_to_res[1005];

void gale_shapley() {
    for(int t=1; t<=n; t++) {
        for(int i=1; i<=n; i++) {
            if(cus_to_res[i]) continue;

            while(idx[i] <= n) {
                int res = cus_like[i][idx[i]];
                if(res_to_cus[res].size() < cap[res]) {
                    cus_to_res[i] = res;
                    res_to_cus[res].push({res_pref[res][i], i});
                    break;
                }
                else if(cap[res]) {
                    pii last = res_to_cus[res].top();
                    if(res_pref[res][i] < last.first) {
                        cus_to_res[last.second] = 0;
                        res_to_cus[res].pop();
                        cus_to_res[i] = res;
                        res_to_cus[res].push({res_pref[res][i], i});
                        break;
                    }
                }
                idx[i]++;
            }
        }
    }
}

// Example usage: n customers and n resources (capacities may exceed 1).
// Reads, in order:
//   each customer's preference list over resources (n ids, most-preferred first),
//   each resource's capacity,
//   each resource's preference order over customers (n ids, most-preferred first).
// Prints each customer's matched resource, 0 if unmatched.
void SolveProblem() {
    cin >> n;
    for(int i=1; i<=n; i++) {
        cus_like[i].resize(n+1);
        idx[i] = 1;
        for(int j=1; j<=n; j++) cin >> cus_like[i][j];
    }
    for(int r=1; r<=n; r++) cin >> cap[r];
    for(int r=1; r<=n; r++) for(int k=1; k<=n; k++) {
        int cus; cin >> cus;
        res_pref[r][cus] = k;
    }

    gale_shapley();

    for(int i=1; i<=n; i++) cout << cus_to_res[i] << " ";
    cout << "\n";
}
