#include <bits/stdc++.h>

void stringSuffix() {
    std::string s;
    std::cin >> s;
    s += "$";
    int n = s.size();
    std::vector<int> p(n), c(n);

    // k = 0
    std::vector<std::pair<char, int> > a(n);
    for (int i = 0; i < n; i++) a[i] = {s[i], i};
    std::ranges::sort(a.begin(), a.end());

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
        std::vector<std::pair<std::pair<int, int>, int> > a(n);
        for (int i = 0; i < n; i++) {
            a[i] = {{c[i], c[i + (1 << k) % n]}, i};
        }
        std::ranges::sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first) {
                c[p[i]] = c[p[i - 1]];
            } else {
                c[p[i]] = c[p[i - 1]] + 1;
            }
        }
        k++;
    }

    for (int i = 0; i < n; i++) {
        std::cout << p[i] << " " << s.substr(p[i], n - p[i]) << "\n";
    }
}

int main() {
    stringSuffix();
}
