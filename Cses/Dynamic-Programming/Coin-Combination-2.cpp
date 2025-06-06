#include <bits/stdc++.h>
 
void Numerator() {
    int n, x;
    int mod = 1e9 + 7;
    std::cin >> n >> x;
    std::vector<int64_t> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
 
    std::vector<std::vector<int> > dp(n + 1, std::vector<int>(x + 1));
 
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }
 
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 1; j <= x; j++) {
            int take = 0;
            int notTake = dp[i + 1][j];
            if (j - a[i] >= 0) {
                take = dp[i][j - a[i]];
            }
            dp[i][j] = (take + notTake) % mod;
        }
    }
 
    std::cout << dp[0][x] << '\n';
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