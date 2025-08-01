const int LOG = 20;

int kth_ancestor(int u, int k, const vector<vector<int>>& up) {
    for (int i = 0; i < LOG; i++) {
        if (k & (1 << i)) {
            u = up[u][i];
            if (u == -1) break;
        }
    }
    return u;
}
void dfs(int v, int p, vector<vector<int>> &adj, vector<vector<int>> &up,
         vector<int> &depth) {
  up[v][0] = p;
  for (int i = 1; i < LOG; i++) {
    if (up[v][i - 1] == -1) break;
    up[v][i] = up[up[v][i - 1]][i - 1];
  }

  for (int u : adj[v]) {
    if (u != p) {
      depth[u] = depth[v] + 1;
      dfs(u, v, adj, up, depth);
    }
  }
}

int lca(int u, int v, const vector<vector<int>> &up, const vector<int> &depth) {
  if (depth[u] < depth[v]) swap(u, v);
  for (int i = LOG - 1; i >= 0; i--)
    if (depth[u] - (1 << i) >= depth[v]) u = up[u][i];
  if (u == v) return u;
  for (int i = LOG - 1; i >= 0; i--)
    if (up[u][i] != up[v][i]) {
      u = up[u][i];
      v = up[v][i];
    }
  return up[u][0];
}
