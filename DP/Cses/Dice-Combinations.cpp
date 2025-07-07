#include <bits/stdc++.h>
 
void Numerator() {
    const int mod = 1e9 + 7;
    int64_t n;
    std::cin >> n;
    int dp[n + 1];
    dp[0] = 1;
    dp[1] = 1;
 
    for (int i = 2; i <= n; i++) {
        int64_t sum = 0;
        for (int j = 1; j <= 6; j++) {
            if (i - j >= 0) {
                sum = (sum + dp[i - j]) % mod;
            }
        }
        dp[i] = sum;
    }
 
    const int ans = dp[n];
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