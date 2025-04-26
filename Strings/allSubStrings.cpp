#include <bits/stdc++.h>
// o(n)
std::set<std::string> allSubStrings(std::string s) {
    std::set<std::string> set;

    const int L = static_cast<int>(s.size());

    for (int i = 0; i < L; i++) {
        for (int j = i + 1; j <= L; j++) {
            set.insert(s.substr(i, j - i));
        }
    }

    return set;
}
