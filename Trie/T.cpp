#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

// ============================================================
// TRIE - COMPLETE
// ============================================================
// FIXED/ADDED:
// 1. 'Void' typo → 'void' in deleteWord
// 2. search() was empty → now implemented
// 3. deleteWord() was empty → now implemented (recursive helper)
// 4. Added: getAllWords() for prefix exploration (Lab 12 GUI needs this)
// ============================================================

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;

    // Helper: recursively collect all words with given prefix
    void collectWords(TrieNode* node, string current, string words[], int& count, int maxCount) {
        if (!node) return;
        if (node->isEndOfWord && count < maxCount)
            words[count++] = current;
        for (auto& pair : node->children)
            collectWords(pair.second, current + pair.first, words, count, maxCount);
    }

    // Helper: recursive delete. Returns true if current node should be deleted.
    bool deleteHelper(TrieNode* node, const string& word, int depth) {
        if (!node) return false;

        // Base case: reached end of word
        if (depth == (int)word.size()) {
            if (!node->isEndOfWord) return false;  // word doesn't exist
            node->isEndOfWord = false;
            // Delete this node only if it has no children
            return node->children.empty();
        }

        char ch = word[depth];
        auto it = node->children.find(ch);
        if (it == node->children.end()) return false;   // word not found

        bool shouldDeleteChild = deleteHelper(it->second, word, depth + 1);

        if (shouldDeleteChild) {
            delete it->second;
            node->children.erase(it);
            // Delete this node only if it's not end of another word and has no children
            return (!node->isEndOfWord && node->children.empty());
        }
        return false;
    }

    // Helper: free entire trie recursively
    void freeNode(TrieNode* node) {
        if (!node) return;
        for (auto& pair : node->children)
            freeNode(pair.second);
        delete node;
    }

public:
    Trie() { root = new TrieNode(); }

    ~Trie() {
        freeNode(root);
        root = nullptr;
    }

    // O(L) where L = word length
    void insertWord(const string& word) {
        TrieNode* curr = root;
        for (char ch : word) {
            if (curr->children.find(ch) == curr->children.end())
                curr->children[ch] = new TrieNode();
            curr = curr->children[ch];
        }
        curr->isEndOfWord = true;
    }

    // FIXED: was completely empty
    // O(L) - returns true only if full word exists (not just prefix)
    bool search(const string& word) {
        TrieNode* curr = root;
        for (char ch : word) {
            auto it = curr->children.find(ch);
            if (it == curr->children.end()) return false;
            curr = it->second;
        }
        return curr->isEndOfWord;   // must be marked as end of word
    }

    // O(L) - returns true if any word has this prefix
    bool searchPrefix(const string& prefix) {
        TrieNode* curr = root;
        for (char ch : prefix) {
            auto it = curr->children.find(ch);
            if (it == curr->children.end()) return false;
            curr = it->second;
        }
        return true;
    }

    // FIXED: 'Void' typo, and was completely empty
    // O(L) - deletes word, cleans up dangling nodes
    void deleteWord(const string& word) {
        if (!search(word)) {
            cout << "Word '" << word << "' not found.\n";
            return;
        }
        deleteHelper(root, word, 0);
        cout << "Deleted: " << word << endl;
    }

    // Returns all words that start with given prefix
    // count = how many words found, stored in words[]
    int getWordsWithPrefix(const string& prefix, string words[], int maxCount) {
        TrieNode* curr = root;
        for (char ch : prefix) {
            auto it = curr->children.find(ch);
            if (it == curr->children.end()) return 0;
            curr = it->second;
        }
        int count = 0;
        collectWords(curr, prefix, words, count, maxCount);
        return count;
    }
};

int main() {
    Trie t;

    cout << "--- Inserting words ---\n";
    t.insertWord("apple");
    t.insertWord("app");
    t.insertWord("apt");
    t.insertWord("bat");
    t.insertWord("ball");
    t.insertWord("band");

    cout << "\n--- Search (exact word) ---\n";
    cout << "search('apple'): " << (t.search("apple") ? "FOUND" : "NOT FOUND") << endl;
    cout << "search('app')  : " << (t.search("app")   ? "FOUND" : "NOT FOUND") << endl;
    cout << "search('ap')   : " << (t.search("ap")    ? "FOUND" : "NOT FOUND") << endl;  // prefix only, not a word

    cout << "\n--- Prefix Search ---\n";
    cout << "prefix('ap')  : " << (t.searchPrefix("ap")  ? "EXISTS" : "NO") << endl;
    cout << "prefix('ba')  : " << (t.searchPrefix("ba")  ? "EXISTS" : "NO") << endl;
    cout << "prefix('xyz') : " << (t.searchPrefix("xyz") ? "EXISTS" : "NO") << endl;

    cout << "\n--- Words with prefix 'ba' ---\n";
    string results[10];
    int n = t.getWordsWithPrefix("ba", results, 10);
    for (int i = 0; i < n; i++) cout << "  " << results[i] << endl;

    cout << "\n--- Delete ---\n";
    t.deleteWord("app");
    cout << "After deleting 'app':\n";
    cout << "search('app')  : " << (t.search("app")   ? "FOUND" : "NOT FOUND") << endl;
    cout << "search('apple'): " << (t.search("apple") ? "FOUND" : "NOT FOUND") << endl;  // should still exist

    system("pause>0");
    return 0;
}