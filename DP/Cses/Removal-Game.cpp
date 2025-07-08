#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include "printer.hpp"
#define print(...) Printer::debug_impl(#__VA_ARGS__, __VA_ARGS__)
#else
#define print(...) 42
#endif


void Numerator() {
    int64_t n;
    std::cin >> n;
    std::vector<int64_t> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
     

    // dp[i][j] => what is the maximum score can be achieved from the subarray from
    // index i....j

    // if first player takes the front element then :
    // his score will increase by arr[i] and now he can get the score from remaining array will be
    // the total sum of score of subarray minus the max score the second player will get
    // dp[i][j] = arr[i] + sum[i + 1][j] - dp[i + 1][j]
    


    std::vector<std::vector<int64_t>> dp(n, std::vector<int64_t>(n, 1e15));

    std::vector<int64_t> sum(n);
    sum[0] = a[0];
    for (int i = 1; i < n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }
    auto getSum = [&](int i, int j) -> int64_t {
        return i == 0 ? sum[j] : sum[j] - sum[i - 1];
    };
    
    std::function<int64_t(int, int)> func = [&](int i, int j) -> int64_t {
        if (i == j) return a[i];
        if (dp[i][j] != 1e15) {
            return dp[i][j];
        }

        dp[i][j] = std::max(a[i] + getSum(i + 1, j) - func(i + 1, j),
                             a[j] + getSum(i, j - 1) - func(i, j - 1));
        return dp[i][j];
    };

    int64_t ans = func(0, n - 1);

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
