#include <bits/stdc++.h>

// Segment Tree with Point Updates and Range Queries
// Supports multiple Segment Trees with just a change in the Node and Update
// Very few changes required everytime

template<typename Node, typename Update>
struct SegTree {
    std::vector<Node> tree;
    std::vector<int64_t> arr; // type may change
    int n;
    int s;

    SegTree(int a_len, std::vector<int64_t> &a) {
        // change if type updated
        arr = a;
        n = a_len;
        s = 1;
        while (s < 2 * n) {
            s = s << 1;
        }
        tree.resize(s);
        fill(tree.begin(), tree.end(), Node());
        build(0, n - 1, 1);
    }

    void build(int start, int end, int index) // Never change this
    {
        if (start == end) {
            tree[index] = Node(arr[start]);
            return;
        }
        int mid = (start + end) / 2;
        build(start, mid, 2 * index);
        build(mid + 1, end, 2 * index + 1);
        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
    }

    void update(int start, int end, int index, int query_index, Update &u) // Never Change this
    {
        if (start == end) {
            u.apply(tree[index]);
            return;
        }
        int mid = (start + end) / 2;
        if (mid >= query_index)
            update(start, mid, 2 * index, query_index, u);
        else
            update(mid + 1, end, 2 * index + 1, query_index, u);
        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
    }

    Node query(int start, int end, int index, int left, int right) {
        // Never change this
        if (start > right || end < left)
            return Node();
        if (start >= left && end <= right)
            return tree[index];
        int mid = (start + end) / 2;
        Node l, r, ans;
        l = query(start, mid, 2 * index, left, right);
        r = query(mid + 1, end, 2 * index + 1, left, right);
        ans.merge(l, r);
        return ans;
    }

    void make_update(int index, int64_t val) {
        // pass in as many parameters as required
        Update new_update = Update(val); // may change
        update(0, n - 1, 1, index, new_update);
    }

    Node make_query(int left, int right) {
        return query(0, n - 1, 1, left, right);
    }
};

struct Node1 {
    int64_t val; // may change
    Node1() {
        // Identity element
        val = 0; // may change
    }

    Node1(int64_t p1) {
        // Actual Node
        val = p1; // may change
    }

    void merge(Node1 &l, Node1 &r) {
        // Merge two child nodes
        val = l.val ^ r.val; // may change
    }
};

struct Update1 {
    int64_t val; // may change
    Update1(int64_t p1) {
        // Actual Update
        val = p1; // may change
    }

    void apply(Node1 &a) {
        // apply update to given node
        a.val = val; // may change
    }
};

void dummyMain() {
    int64_t n, m;
    std::cin >> n >> m;
    std::vector<int64_t> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    SegTree<Node1, Update1> segTree = SegTree<Node1, Update1>(n, arr);
    segTree.make_update(2,5);
}
