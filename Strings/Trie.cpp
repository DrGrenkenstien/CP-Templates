#include <bits/stdc++.h>

using namespace std;

class TrieNode{
    public:
    bool isend = false;
    TrieNode* children[26] = {nullptr};
};

class Trie {
    TrieNode* root;

    public:
        Trie() {
        this->root = new TrieNode();
    }

    void insert(string word) {

        TrieNode *node = root;

        for(char c: word){

            if(!node->children[c - 'a'])
                node->children[c - 'a'] = new TrieNode();

            node = node->children[c - 'a'];

        }

        node->isend = true;

    }

    bool search(string word) {

        TrieNode *node = root;

        for(char c : word){

            if(!node->children[c - 'a'])
                return false;
            node = node->children[c - 'a'];

        }

        return node->isend;

    }
};

int main(){
    return 0;
}
    

