#include <unordered_map>
#include <string>

using namespace std;

struct TrieNode {
    bool isEnd;
    unordered_map<char, TrieNode*> children;
    
    TrieNode() : isEnd(false) {}
};

class Trie {
private:
    TrieNode* root;
    
public:
    // Constructor
    Trie() {
        root = new TrieNode();
    }
    
    // Destructor to prevent memory leaks
    ~Trie() {
        // Optional: Implement recursive deletion if needed
        deleteTrie(root);
    }
    
private:
    // Helper function for destructor
    void deleteTrie(TrieNode* node) {
        if (!node) return;
        for (auto& pair : node->children) {
            deleteTrie(pair.second);
        }
        delete node;
    }
    
public:
    // Insert a word into the Trie
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {//this means that the character c is not present in the children of the current node, so we need to create a new TrieNode for it.
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEnd = true;
    }
    
    // Search for a complete word
    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return node->isEnd;
    }
    
    // Check if any word starts with the given prefix
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return true;
    }
    
    // Optional: Delete a word from the Trie
    bool remove(string word) {
        return removeHelper(root, word, 0);
    }
    
private:
    bool removeHelper(TrieNode* node, const string& word, int index) {
        if (!node) return false;
        
        if (index == word.length()) {
            if (!node->isEnd) return false;
            node->isEnd = false;
            return node->children.empty(); // Can be deleted if no children
        }
        
        char c = word[index];
        auto it = node->children.find(c);
        if (it == node->children.end()) return false;
        
        bool shouldDeleteChild = removeHelper(it->second, word, index + 1);
        
        if (shouldDeleteChild) {
            delete it->second;
            node->children.erase(c);
            return !node->isEnd && node->children.empty();
        }
        
        return false;
    }
};