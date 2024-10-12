#include <bits/stdc++.h>

struct Node {
    Node *link[26];
    bool flag;

    Node() {
        for (int i = 0; i < 26; i++) {
            link[i] = nullptr;
        }
        flag = false;
    }

    bool containsKey(char ch) {
        return link[ch - 'a'] != NULL;
    }

    void put(char ch, Node *node) {
        link[ch - 'a'] = node;
    }
};

class Trie {
public:
    Node *root;

public:
    Trie() {
        root = new Node;
    }

    void insert(std::string &word) {
        Node *node = root;
        for (int i = 0; i < word.size(); i++) {
            if (!node->containsKey(word[i])) {
                node->put(word[i], new Node());
            }
            node = node->link[word[i] - 'a'];
        }
        node->flag = true;
    }

    bool search(std::string &word) {
        Node *node = root;
        for (int i = 0; i < word.size(); i++) {
            if (!node->containsKey(word[i])) {
                return false;
            }
            node = node->link[word[i] - 'a'];
        }

        return node->flag;
    }

    bool startsWith(std::string &word) {
        Node *node = root;
        for (int i = 0; i < word.size(); i++) {
            if (!node->containsKey(word[i])) {
                return false;
            }
            node = node->link[word[i] - 'a'];
        }
        return true;
    }
};

int main() {
    Trie tr;
    std::string s1 = "numerator";
    std::string s2 = "num";
    std::string s3 = "numr";
    tr.insert(s1);

    if (tr.search(s1)) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    if (tr.startsWith(s2)) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    if (tr.startsWith(s3)) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
}
