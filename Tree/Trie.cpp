#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

class Node {
    // Standard alphabet size for lowercase 'a'-'z'
    static const int ALPHABET_SIZE = 26;
    bool isEnd = false;
    vector<unique_ptr<Node>> children;

public:
    Node() {
        // Only resize to what is necessary
        children.resize(ALPHABET_SIZE);
    }

    Node* getChild(char c) {
        int index = c - 'a';
        if (index < 0 || index >= ALPHABET_SIZE) return nullptr;
        return children[index].get();
    }

    void addChild(char c) {
        int index = c - 'a';
        if (index >= 0 && index < ALPHABET_SIZE && !children[index]) {
            children[index] = make_unique<Node>();
        }
    }

    void setEndOfWord(bool status) { isEnd = status; }
    bool getEndOfWord() const { return isEnd; }
};

class Trie {
    unique_ptr<Node> root;

public:
    Trie() : root(make_unique<Node>()) {}

    void insert(const string& word) {
        Node* curr = root.get();
        for (char c : word) {
            if (curr->getChild(c) == nullptr) {
                curr->addChild(c);
            }
            curr = curr->getChild(c);
        }
        curr->setEndOfWord(true);
    }

    bool search(const string& word) {
        Node* curr = root.get();
        for (char c : word) {
            curr = curr->getChild(c);
            if (curr == nullptr) return false;
        }
        return curr->getEndOfWord();
    }

    bool startsWith(const string& prefix) {
        Node* curr = root.get();
        for (char c : prefix) {
            curr = curr->getChild(c);
            if (curr == nullptr) return false;
        }
        return true;
    }
};