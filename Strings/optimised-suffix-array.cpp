#include <bits/stdc++.h>

void count_sort(std::vector<int> &p, std::vector<int> &c) {
    int n = p.size();
    std::vector<int> cnt(n);
    for (auto x: c) {
        cnt[x]++;
    }

    std::vector<int> p_new(n);
    std::vector<int> pos(n);
    pos[0] = 0;
    for (int i = 1; i < n; i++) {
        pos[i] = pos[i - 1] + cnt[i - 1];
    }

    for (auto x: p) {
        int i = c[x];
        p_new[pos[i]] = x;
        pos[i]++;
    }
    p = p_new;
}


void stringSuffix() {
    std::string s;
    std::cin >> s;
    s += "$";
    int n = s.size();
    std::vector<int> p(n), c(n);

    // k = 0
    std::vector<std::pair<char, int> > a(n);
    for (int i = 0; i < n; i++) a[i] = {s[i], i};
    std::sort(a.begin(), a.end());

    for (int i = 0; i < n; i++) p[i] = a[i].second;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++) {
        if (a[i].first == a[i - 1].first) {
            c[p[i]] = c[p[i - 1]];
        } else {
            c[p[i]] = c[p[i - 1]] + 1;
        }
    }
    int k = 0;
    while ((1 << k) < n) {
        // k -> k + 1
        for (int i = 0; i < n; i++) {
            p[i] = (p[i] - (1 << k) + n) % n;
        }

        count_sort(p, c);

        std::vector<int> c_new(n);
        c_new[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            std::pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            std::pair<int, int> now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            if (now == prev) {
                c_new[p[i]] = c_new[p[i - 1]];
            } else {
                c_new[p[i]] = c_new[p[i - 1]] + 1;
            }
        }
        c = c_new;
        k++;
    }

    for (int i = 0; i < n; i++) {
        std::cout << p[i] << " " << s.substr(p[i], n - p[i]) << "\n";
    }
}


int main() {
    stringSuffix();
}
