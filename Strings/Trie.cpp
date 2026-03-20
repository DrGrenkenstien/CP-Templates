#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    bool isEnd = false;
    array<unique_ptr<TrieNode>, 26> children{};
};

class Trie {
    unique_ptr<TrieNode> root;

public:
    Trie() {
        root = make_unique<TrieNode>();
    }

    void insert(const string& word) {
        TrieNode* node = root.get();  // non-owning raw pointer

        for (char c : word) {
            int idx = c - 'a';

            if (!node->children[idx]) {
                node->children[idx] = make_unique<TrieNode>();
            }

            node = node->children[idx].get();
        }

        node->isEnd = true;
    }

    bool search(const string& word) const {
        TrieNode* node = root.get();

        for (char c : word) {
            int idx = c - 'a';

            if (!node->children[idx])
                return false;

            node = node->children[idx].get();
        }

        return node->isEnd;
    }
};

int main() {
    Trie t;
    t.insert("apple");
    cout << t.search("apple") << endl;   // 1
    cout << t.search("app") << endl;     // 0
}
