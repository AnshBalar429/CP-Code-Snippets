#include <bits/stdc++.h>
 
void Numerator() {
    int n, x;
    int mod = 1e9 + 7;
    std::cin >> n >> x;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
 
    std::vector<int> dp(x + 1, 0);
    dp[0] = 1;
 
    for (int i = 1; i <= x; i++) {
        if (dp[i] == 0) {
            int sum = 0;
            for (int j = 0; j < n; j++) {
                if (i - a[j] >= 0) {
                    sum = (sum + dp[i - a[j]]) % mod;
                }
            }
            dp[i] = sum;
        }
    }
 
    std::cout << dp[x] << '\n';
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
