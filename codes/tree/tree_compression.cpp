vector<pii> edges1[500005];

int build_virtual_tree(vi &nodes) {
    sort(all(nodes)); nodes.erase(unique(all(nodes)), nodes.end());
    sort(all(nodes), cmp_in);

    int k = nodes.size();
    for(int i=0; i<k-1; i++) nodes.push_back(find_lca(nodes[i], nodes[i+1]));
    sort(all(nodes)); nodes.erase(unique(all(nodes)), nodes.end());
    sort(all(nodes), cmp_in);

    for(int i=0; i<(int)nodes.size()-1; i++) {
        int a = nodes[i], b = nodes[i+1];
        int p = find_lca(a, b);
        edges1[p].push_back({b, depth[b]-depth[p]});
    }
    return nodes[0];
}
