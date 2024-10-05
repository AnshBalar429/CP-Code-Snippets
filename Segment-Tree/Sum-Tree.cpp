#include <bits/stdc++.h>

// Simple Segment tree for sum range queries.
std::vector<int> segTree;

void build(std::vector<int> &arr, int start, int end, int ind) {
    if (start == end) {
        segTree[ind] = arr[start];
        return;
    }
    const int mid = (start + end) / 2;
    const int left = 2 * ind;
    const int right = 2 * ind + 1;
    build(arr, start, mid, left);
    build(arr, mid + 1, end, right);
    segTree[ind] = segTree[left] + segTree[right];
}

void update(std::vector<int> &arr, int start, int end, int ind, int pos, int value) {
    if (start == end) {
        //might change
        arr[pos] = value;
        segTree[ind] = arr[pos];
        return;
    }

    int mid = (start + end) / 2;
    if (mid >= pos) {
        update(arr, start, mid, 2 * ind, pos, value);
    } else {
        update(arr, mid + 1, end, 2 * ind + 1, pos, value);
    }

    //might change
    segTree[ind] = segTree[2 * ind] + segTree[2 * ind + 1];
}

int query(int start, int end, int ind, int l, int r) {
    //complete overlap
    if (start >= l && end <= r) {
        return segTree[ind];
    }

    if (l > end || r < start) {
        return 0;
    }

    int mid = (start + end) / 2;
    int leftans = query(start, mid, 2 * ind, l, r);
    int rightans = query(mid + 1, end, 2 * ind + 1, l, r);
    //might change
    return leftans + rightans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cout << std::fixed << std::setprecision(25);

    int n;
    std::cin >> n;
    segTree.resize(2 * n, -1);
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];;
    }

    // building segment tree
    // start --> starting pos of arr
    // end --> ending pos of arr
    // ind --> index of root node of segment tree
    build(arr, 0, n - 1, 1);
    for (auto it: segTree) {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    // pos --> position to where change (0 based indexing)
    update(arr, 0, n - 1, 1, 1, 10);

    // l to r --> query range from l to r
    const int ans = query(0, n - 1, 1, 2, 4);
    std::cout << ans << std::endl;

    return 0;
}
