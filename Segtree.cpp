class Segtree {
public:
    vector<int> tree, lazy;

    Segtree(vector<int> &a) {
        int n = a.size();
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
        build(a, 0, 0, n - 1);
    }

    void build(vector<int> &a, int v, int l, int r) {
        if (l == r) {
            tree[v] = a[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(a, 2 * v + 1, l, mid);
        build(a, 2 * v + 2, mid + 1, r);
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }

    void push(int v, int l, int r) {
        if (lazy[v] != 0) {
            tree[v] += (r - l + 1) * lazy[v];
            if (l != r) {
                lazy[2 * v + 1] += lazy[v];
                lazy[2 * v + 2] += lazy[v];
            }
            lazy[v] = 0;
        }
    }

    void pointUpdate(int v, int l, int r, int pos, int value) {
        push(v, l, r);
        if (l == r) {
            tree[v] = value;
            return;
        }
        int mid = l + (r - l) / 2;
        if (pos <= mid) {
            pointUpdate(2 * v + 1, l, mid, pos, value);
        } else {
            pointUpdate(2 * v + 2, mid + 1, r, pos, value);
        }
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }

    void rangeUpdate(int v, int l, int r, int lx, int rx, int value) {
        push(v, l, r);
        if (lx > rx) return;
        if (l == lx && r == rx) {
            lazy[v] += value;
            push(v, l, r);
            return;
        }
        int mid = l + (r - l) / 2;
        rangeUpdate(2 * v + 1, l, mid, lx, min(rx, mid), value);
        rangeUpdate(2 * v + 2, mid + 1, r, max(lx, mid + 1), rx, value);
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }

    int rangeSum(int v, int l, int r, int lx, int rx) {
        push(v, l, r);
        if (lx > rx) return 0;
        if (l == lx && r == rx) {
            return tree[v];
        }
        int mid = l + (r - l) / 2;
        return rangeSum(2 * v + 1, l, mid, lx, min(rx, mid)) +
               rangeSum(2 * v + 2, mid + 1, r, max(lx, mid + 1), rx);
    }
};
