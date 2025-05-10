#include <bits/stdc++.h>

const int mod = 998244353;

struct mint {
    int x;

    mint() { x = 0; }
    mint(int32_t xx) { 
        x = xx % mod; 
        if (x < 0) x += mod; 
    }
    mint(int64_t xx) { 
        x = int(xx % mod); 
        if (x < 0) x += mod; 
    }

    int val() const {
        return x;
    }

    mint& operator++() {
        x++;
        if (x == mod) x = 0;
        return *this;
    }

    mint& operator--() {
        if (x == 0) x = mod;
        x--;
        return *this;
    }

    mint operator++(int32_t) {
        mint result = *this;
        ++*this;
        return result;
    }

    mint operator--(int32_t) {
        mint result = *this;
        --*this;
        return result;
    }

    mint& operator+=(const mint& b) {
        x += b.x;
        if (x >= mod) x -= mod;
        return *this;
    }

    mint& operator-=(const mint& b) {
        x -= b.x;
        if (x < 0) x += mod;
        return *this;
    }

    mint& operator*=(const mint& b) {
        int64_t z = int64_t(x) * b.x;
        x = int(z % mod);
        return *this;
    }

    mint operator+() const {
        return *this;
    }

    mint operator-() const {
        return mint() - *this;
    }

    mint& operator/=(const mint& b) {
        return *this = *this * b.inv();
    }

    mint power(int64_t n) const {
        mint base = *this, result = 1;
        while (n > 0) {
            if (n & 1) result *= base;
            base *= base;
            n >>= 1;
        }
        return result;
    }

    mint inv() const {
        return power(mod - 2);
    }

    friend mint operator+(const mint& a, const mint& b) {
        return mint(a) += b;
    }

    friend mint operator-(const mint& a, const mint& b) {
        return mint(a) -= b;
    }

    friend mint operator*(const mint& a, const mint& b) {
        return mint(a) *= b;
    }

    friend mint operator/(const mint& a, const mint& b) {
        return mint(a) /= b;
    }

    friend bool operator==(const mint& a, const mint& b) {
        return a.x == b.x;
    }

    friend bool operator!=(const mint& a, const mint& b) {
        return a.x != b.x;
    }

    mint power(mint a, int64_t n) {
        return a.power(n);
    }

    friend std::ostream& operator<<(std::ostream& os, const mint& m) {
        os << m.x;
        return os;
    }

    explicit operator bool() const {
        return x != 0;
    }
};