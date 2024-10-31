#include <bits/stdc++.h>
class Mex {
private:
    std::map<int, int> frequency;
    std::set<int> missing_numbers;
    std::vector<int> A;

public:
    Mex(std::vector<int> const& A) : A(A) {
        for (int i = 0; i <= A.size(); i++)
            missing_numbers.insert(i);

        for (int x : A) {
            ++frequency[x];
            missing_numbers.erase(x);
        }
    }

    int mex() {
        return *missing_numbers.begin();
    }

    void update(int idx, int new_value) {
        if (--frequency[A[idx]] == 0)
            missing_numbers.insert(A[idx]);
        A[idx] = new_value;
        ++frequency[new_value];
        missing_numbers.erase(new_value);
    }
};

void main() {
    std::vector<int> a{0,1,2,3,4,6,7,8,9};
    Mex mex(a);
    int ans = mex.mex();
    std::cout << ans << std::endl;
    mex.update(4,5);
    ans = mex.mex();
    std::cout << ans << std::endl;

}