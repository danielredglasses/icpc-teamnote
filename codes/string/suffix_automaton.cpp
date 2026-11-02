// Time: O(n) construction over a fixed alphabet (O(1) per char via the ch[26] array;
// swap in a map<int,int> for a large/sparse alphabet).
// 0 = null; node counter starts at 0, root/initial state = node 1
// (allocated via ++node_cnt).
struct sam_node { int len, link, ch[26]; };
sam_node sam[1000005]; int node_cnt = 0, root, last; // size = 2 * max string length

int sam_new_node() {
    int id = ++node_cnt;
    sam[id].len = sam[id].link = 0;
    fill(sam[id].ch, sam[id].ch+26, 0);
    return id;
}

void sam_init() {
    node_cnt = 0;
    root = last = sam_new_node();
}

// c = 0-indexed character id (e.g. s[i]-'a')
void sam_extend(int c) {
    int cur = sam_new_node();
    sam[cur].len = sam[last].len + 1;
    int p = last;
    while(p && !sam[p].ch[c]) {
        sam[p].ch[c] = cur;
        p = sam[p].link;
    }
    if(!p) sam[cur].link = root;
    else {
        int q = sam[p].ch[c];
        if(sam[p].len + 1 == sam[q].len) sam[cur].link = q;
        else {
            int clone = sam_new_node();
            sam[clone] = sam[q];
            sam[clone].len = sam[p].len + 1;
            while(p && sam[p].ch[c] == q) {
                sam[p].ch[c] = clone;
                p = sam[p].link;
            }
            sam[q].link = sam[cur].link = clone;
        }
    }
    last = cur;
}

// usage: sam_init(); for each char c of s (in order), sam_extend(c - 'a');
// each state represents an equivalence class of substrings ending at the
// same set of positions;
// number of distinct substrings of s = sum over all non-root states of
// (len[state] - len[link[state]])
