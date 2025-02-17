#include <bits/stdc++.h>
// Code for finding K-th parent of any node 
// dp[node][i] represents the 2^i-th parent of node
constexpr int maxN = 2e5 + 7;
int64_t dp[maxN][20];
 
void Numerator() {
    // Binary Lifting
    int64_t n, q;
    std::cin >> n >> q;
 
    std::vector<std::vector<int64_t> > adj(n + 1);
 
    std::function<void(int64_t, int64_t)> dfs = [&](int64_t node, int64_t par) -> void {
        dp[node][0] = par;
        for (int i = 1; i < 20; i++) {
            dp[node][i] = dp[dp[node][i - 1]][i - 1];
        }
 
        for (const auto &it: adj[node]) {
            if (it == par) continue;
            dfs(it, node);
        }
    };
 
    for (int i = 1; i < n; i++) {
        int64_t num;
        std::cin >> num;
        adj[num].push_back(i + 1);
        adj[i + 1].push_back(num);
    }
 
    dfs(1, 0);
 
    while (q--) {
        int64_t x, k;
        std::cin >> x >> k;
        int64_t ans = x;
        for (int i = 20; i >= 0; i--) {
            if ((k >> i) & 1) {
                ans = dp[ans][i];
            }
        }
        if (ans)
            std::cout << ans << '\n';
        else
            std::cout << -1 << '\n';
    }
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