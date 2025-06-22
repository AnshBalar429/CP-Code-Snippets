#include <bits/stdc++.h>
 
void Numerator() {
    int n, x;
    std::cin >> n >> x;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
 
    std::vector<int> dp(x + 1, 1e9);
    dp[0] = 0;
 
    for (int i = 1; i <= x; i++) {
        for (int j = 0; j < n; j++) {
            if (i - a[j] >= 0) {
                dp[i] = std::min(dp[i], dp[i - a[j]] + 1);
            }
        }
    }
 
    std::cout << (dp[x] < 1e9 ? dp[x] : -1) << '\n';
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