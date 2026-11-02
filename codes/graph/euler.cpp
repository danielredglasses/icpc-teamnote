// euler_path: there should be 0 or 2 odd degree nodes
// euler circuit: there should be 0 odd degree nodes
vi edges[100005];
int edge_idx[100005];

void euler(int index) {
    while(edge_idx[index] < edges[index].size()) {
        int cur = edges[index][edge_idx[index]++];
        euler(cur);
    }
    cout << index << " ";
}