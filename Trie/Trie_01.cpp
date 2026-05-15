#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

const int ALPHABET_SIZE = 26;

//---------------------------
// Standalone Node Structure
//---------------------------
struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }
};

//---------------------------
// Trie Class for Suggestions
//---------------------------
class Trie {
private:
    TrieNode* root;

    void clear(TrieNode* node) {
        if (node == nullptr) return;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            clear(node->children[i]);
        }
        delete node;
    }

    int getCharIndex(char c) {
        return tolower(c) - 'a';
    }

    // Helper: DFS to collect all words starting from a specific node
    void collectAllWords(TrieNode* node, string currentPrefix) {
        if (node == nullptr) return;

        // If this node marks the end of a word, print it
        if (node->isEndOfWord) {
            cout << "  - " << currentPrefix << endl;
        }

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i] != nullptr) {
                char nextChar = 'a' + i;
                collectAllWords(node->children[i], currentPrefix + nextChar);
            }
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        clear(root);
    }

    void insert(string word) {
        TrieNode* current = root;
        for (char c : word) {
            if (!isalpha(c)) continue; // Skip non-alphabetic chars
            int index = getCharIndex(c);
            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    // Displays all words that start with the given prefix
    void displaySuggestions(string prefix) {
        TrieNode* current = root;
        
        // 1. Navigate to the end of the prefix
        for (char c : prefix) {
            int index = getCharIndex(c);
            if (current->children[index] == nullptr) {
                cout << " (No suggestions found for '" << prefix << "')" << endl;
                return;
            }
            current = current->children[index];
        }

        // 2. Perform DFS from that node to find all completions
        collectAllWords(current, prefix);
    }
};

//---------------------------
// File Handling Function
//---------------------------
void loadDictionary(Trie& t, string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return;
    }
    string word;
    while (file >> word) {
        t.insert(word);
    }
    file.close();
    cout << "Dictionary loaded successfully.\n" << endl;
}

//---------------------------
// Main Logic
//---------------------------
int main() {
    Trie searchEngine;

    // Load words (Ensure words.txt exists in your project folder)
    loadDictionary(searchEngine, "words.txt");

    string testPrefixes[] = {"app", "ban", "cat", "z"};

    cout << "--- Real-time Suggestion Simulation ---" << endl;

    for (string fullPrefix : testPrefixes) {
        string currentInput = "";
        cout << "\nTesting sequence for: " << fullPrefix << endl;
        
        // Simulate character-by-character typing
        for (char c : fullPrefix) {
            currentInput += c;
            cout << "User typed: [" << currentInput << "]" << endl;
            cout << "Suggestions:" << endl;
            searchEngine.displaySuggestions(currentInput);
            cout << "-----------------------" << endl;
        }
    }

    system("pause>0");
    return 0;
}