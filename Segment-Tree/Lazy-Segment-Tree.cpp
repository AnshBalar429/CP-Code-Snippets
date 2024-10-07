#include <bits/stdc++.h>

// Lazy Segment Tree with Range Updates and Range Queries
// Supports multiple Segment Trees with just a change in the Node and Update
// Very few changes required everytime

template<typename Node, typename Update>
struct LazySGT {
    std::vector<Node> tree;
    std::vector<bool> lazy;
    std::vector<Update> updates;
    std::vector<int64_t> arr; // type may change
    int n;
    int s;

    LazySGT(int a_len, std::vector<int64_t> &a) {
        // change if type updated
        arr = a;
        n = a_len;
        s = 1;
        while (s < 2 * n) {
            s = s << 1;
        }
        tree.resize(s);
        fill(tree.begin(), tree.end(), Node());
        lazy.resize(s);
        fill(lazy.begin(), lazy.end(), false);
        updates.resize(s);
        fill(updates.begin(), updates.end(), Update());
        build(0, n - 1, 1);
    }

    void build(int start, int end, int index) {
        // Never change this
        if (start == end) {
            tree[index] = Node(arr[start]);
            return;
        }
        int mid = (start + end) / 2;
        build(start, mid, 2 * index);
        build(mid + 1, end, 2 * index + 1);
        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
    }

    void pushdown(int index, int start, int end) {
        if (lazy[index]) {
            int mid = (start + end) / 2;
            apply(2 * index, start, mid, updates[index]);
            apply(2 * index + 1, mid + 1, end, updates[index]);
            updates[index] = Update();
            lazy[index] = 0;
        }
    }

    void apply(int index, int start, int end, Update &u) {
        if (start != end) {
            lazy[index] = 1;
            updates[index].combine(u, start, end);
        }
        u.apply(tree[index], start, end);
    }

    void update(int start, int end, int index, int left, int right, Update &u) {
        // Never Change this
        if (start > right || end < left)
            return;
        if (start >= left && end <= right) {
            apply(index, start, end, u);
            return;
        }
        pushdown(index, start, end);
        int mid = (start + end) / 2;
        update(start, mid, 2 * index, left, right, u);
        update(mid + 1, end, 2 * index + 1, left, right, u);
        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
    }

    Node query(int start, int end, int index, int left, int right) {
        // Never change this
        if (start > right || end < left)
            return Node();
        if (start >= left && end <= right) {
            pushdown(index, start, end);
            return tree[index];
        }
        pushdown(index, start, end);
        int mid = (start + end) / 2;
        Node l, r, ans;
        l = query(start, mid, 2 * index, left, right);
        r = query(mid + 1, end, 2 * index + 1, left, right);
        ans.merge(l, r);
        return ans;
    }

    void make_update(int left, int right, int64_t val) {
        // pass in as many parameters as required
        Update new_update = Update(val); // may change
        update(0, n - 1, 1, left, right, new_update);
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
        val = l.val + r.val; // may change
    }
};

struct Update1 {
    int64_t val; // may change
    Update1() {
        // Identity update
        val = 0;
    }

    Update1(int64_t val1) {
        // Actual Update
        val = val1;
    }

    void apply(Node1 &a, int start, int end) {
        // apply update to given node
        a.val = val * (end - start + 1); // may change
    }

    void combine(Update1 &new_update, int start, int end) {
        val = new_update.val;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cout << std::fixed << std::setprecision(25);

    int n;
    std::cin >> n;
    std::vector<int64_t> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    LazySGT<Node1, Update1> seg = LazySGT<Node1, Update1>(n, a);
    auto ans = seg.make_query(0, n - 1);
    std::cout << ans.val << std::endl;

    ans = seg.make_query(1, 2);
    std::cout << ans.val << std::endl;

    seg.make_update(0, 1, 10);


    ans = seg.make_query(0, 1);
    std::cout << ans.val << std::endl;

    return 0;
}
