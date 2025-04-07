#include <bits/stdc++.h>

struct SparseTable {
    int n, LOG;
    std::vector<std::vector<int> > table;

    static int merge(int x, int y) {
        return std::min(x, y);
    }

    explicit SparseTable(const std::vector<int> &a) : n(size(a)), LOG(std::__lg(n)),
                                                      table(n, std::vector<int>(LOG + 1, -1)) {
        for (int j = 0; j <= LOG; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                if (j == 0)
                    table[i][j] = a[i];
                else
                    table[i][j] = merge(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r) {
        int j = std::__lg(r - l + 1);
        return merge(table[l][j], table[r - (1 << j) + 1][j]);
    }
};