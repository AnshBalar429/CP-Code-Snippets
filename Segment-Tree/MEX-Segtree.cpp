#include <bits/stdc++.h>

const int MAX_VAL = 32;

struct NodeMex {
    unsigned int mask;

    NodeMex() : mask(0) {
    }

    NodeMex(int val) {
        if (val < MAX_VAL)
            mask = (1U << val);
        else
            mask = 0;
    }

    void merge(const NodeMex &l, const NodeMex &r) {
        mask = l.mask | r.mask;
    }

    int getMex() const {
        for (int i = 0; i < MAX_VAL; i++) {
            if (!(mask & (1U << i)))
                return i;
        }
        return MAX_VAL;
    }
};

struct UpdateMex {
    int val;

    UpdateMex(int v) : val(v) {
    }

    void apply(NodeMex &node) {
        if (val < MAX_VAL)
            node.mask = (1U << val);
        else
            node.mask = 0;
    }
};

template<typename Node, typename Update>
struct SegTree {
    std::vector<Node> tree;
    std::vector<int64_t> arr;
    int n;
    int s;

    SegTree(int a_len, std::vector<int64_t> &a) {
        arr = a;
        n = a_len;
        s = 1;
        while (s < 2 * n)
            s = s << 1;
        tree.resize(s);
        std::fill(tree.begin(), tree.end(), Node());
        build(0, n - 1, 1);
    }

    void build(int start, int end, int index) {
        if (start == end) {
            tree[index] = Node(arr[start]);
            return;
        }
        int mid = (start + end) / 2;
        build(start, mid, 2 * index);
        build(mid + 1, end, 2 * index + 1);
        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
    }

    void update(int start, int end, int index, int query_index, Update &u) {
        if (start == end) {
            u.apply(tree[index]);
            return;
        }
        int mid = (start + end) / 2;
        if (query_index <= mid)
            update(start, mid, 2 * index, query_index, u);
        else
            update(mid + 1, end, 2 * index + 1, query_index, u);
        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
    }

    Node query(int start, int end, int index, int left, int right) {
        if (start > right || end < left)
            return Node();
        if (start >= left && end <= right)
            return tree[index];
        int mid = (start + end) / 2;
        Node l = query(start, mid, 2 * index, left, right);
        Node r = query(mid + 1, end, 2 * index + 1, left, right);
        Node ans;
        ans.merge(l, r);
        return ans;
    }

    void make_update(int index, int64_t val) {
        Update new_update(val);
        update(0, n - 1, 1, index, new_update);
    }

    Node make_query(int left, int right) {
        return query(0, n - 1, 1, left, right);
    }
};


void Numerator() {
    std::vector<int64_t> a = {0, 1, 2, 3, 4, 5, 6};
    int n = a.size();

    SegTree<NodeMex, UpdateMex> tree(n, a);

    int ans = tree.make_query(0, n - 1).getMex();
    std::cout << ans << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cout << std::fixed << std::setprecision(25);
    int64_t t = 1;
    // std::cin >> t;
    while (t-- > 0) {
        Numerator();
    }
    return 0;
}
