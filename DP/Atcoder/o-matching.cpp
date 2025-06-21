#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include "printer.hpp"
#define print(...) Printer::debug_impl(#__VA_ARGS__, __VA_ARGS__)
#else
#define print(...) 42
#endif

void Numerator() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    }

    // mask => ith bit is set if ith women is matched with current man

    std::vector<int> dp(1 << n, -1);

    const int mod = 1E9 + 7;

    std::function<int(int)> func = [&](int mask) -> int {
        int ind = __builtin_popcount(mask);
        int ans = 0;
        if (ind == n) {
            return 1;
        }
        if (dp[mask] != -1) {
            return dp[mask];
        }

        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i)) && a[ind][i]) {
                ans = (ans + func(mask | (1 << i))) % mod;
            }
        }
        return dp[mask] = ans;
    };

    int ans = func(0);

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
