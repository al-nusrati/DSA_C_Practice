#include <iostream>
#include <queue> // For priority_queue (Min-Heap) to build the Huffman Tree
#include <unordered_map> // For counting character frequencies efficiently | provides with functions like find, insert, and erase with average O(1) time complexity
#include <string>
using namespace std;

// ─────────────────────────────────────────────
// CLASS: HuffmanNode
// Represents one node in the Huffman Tree.
// A leaf node holds a real character.
// An internal node holds '$' (dummy) and a summed frequency.
// ─────────────────────────────────────────────
class HuffmanNode {
public:
    char data;          // Character ('$' for internal nodes)
    int freq;           // Frequency of the character
    HuffmanNode* left;
    HuffmanNode* right;

    // Constructor — initializes the node cleanly
    HuffmanNode(char data, int freq) {
        this->data  = data;
        this->freq  = freq;
        this->left  = nullptr;
        this->right = nullptr;
    }
};

// ─────────────────────────────────────────────
// COMPARATOR for the Min-Heap (Priority Queue)
// By default, C++ priority_queue is a Max-Heap.
// We flip the comparison so the LOWEST frequency
// node always sits at the top — that's our Min-Heap.
// ─────────────────────────────────────────────
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq; // flip for Min-Heap
    }
};

// ─────────────────────────────────────────────
// CLASS: HuffmanTree
// Encapsulates the entire Huffman algorithm.
// Build → Encode → Decode → Print — all in one clean object.
// ─────────────────────────────────────────────
class HuffmanTree {
private:
    HuffmanNode* root; // Root of the final tree

    // ── PRIVATE HELPER: Recursive DFS ──
    // Walks the tree and stores the binary code for each leaf.
    // 'code' builds up like: left = "0", right = "1"
    void encode(HuffmanNode* node, string code, unordered_map<char, string>& huffmanCode) {
        // Base case: null node, do nothing
        if (node == nullptr) return;

        // Leaf node — store the code for this character
        if (!node->left && !node->right) {
            huffmanCode[node->data] = code;
        }

        // Recurse left (append "0") and right (append "1")
        encode(node->left,  code + "0", huffmanCode);
        encode(node->right, code + "1", huffmanCode);
    }

    // ── PRIVATE HELPER: Free memory ──
    // Post-order traversal to delete every node (left → right → root)
    // Always pair new with delete. Always.
    void deleteTree(HuffmanNode* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    // Constructor — sets root to null initially
    HuffmanTree() : root(nullptr) {}

    // Destructor — cleans up heap memory when object goes out of scope
    ~HuffmanTree() {
        deleteTree(root);
    }

    // ── PUBLIC: Build the tree ──
    // Takes a string, counts character frequencies automatically,
    // then builds the Huffman Tree. O(N log N) total.
    void build(const string& text) {

        // Step 1: Count how many times each character appears
        // unordered_map gives O(1) average lookup — perfect here
        unordered_map<char, int> freqMap; // char → frequency | this map will hold the frequency of each character in the input string
        for (char ch : text) {
            freqMap[ch]++; // if key doesn't exist, it's created as 0 then incremented
        }

        // Step 2: Push all characters as leaf nodes into the Min-Heap
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq; // Min-Heap based on frequency, its structure is behind the scenes a binary tree where each node is a HuffmanNode* and the heap property is maintained based on the frequency of the nodes. The Compare struct defines how to compare two HuffmanNode* for ordering in the heap.  if parent freq > child freq → swap, otherwise keep as is. This ensures that the node with the smallest frequency is always at the top of the heap.

        //------------------------------
        // The loop iterates through each key-value pair in the freqMap, where the key is a character and the value is its frequency. For each pair, it creates a new HuffmanNode with the character and its frequency, and pushes that node into the priority queue (Min-Heap). This sets up the initial heap with all characters as leaf nodes, ready for the merging process to build the Huffman Tree.
        // The time complexity of this loop is O(M log M), where M is the number of unique characters, because each insertion into the priority queue takes O(log M) time and we do it for each of the M unique characters.
        // push() is a member function of the priority_queue class in C++. It is used to add an element to the priority queue while maintaining the heap property. When you call pq.push(element), the new element is added to the end of the underlying container (usually a vector), and then the heap property is restored by comparing the new element with its parent and swapping if necessary. This process continues up the tree until the heap property is satisfied. The time complexity of push() is O(log N) in the worst case, where N is the number of elements in the priority queue, because it may need to traverse up the height of the tree to restore the heap property.
        for (auto& pair : freqMap) {
            pq.push(new HuffmanNode(pair.first, pair.second));
        }

        // This loop continues until there is only one node left in the priority queue, which will be the root of the complete Huffman Tree. In each iteration, it pops the two nodes with the lowest frequency, merges them into a new internal node (with a combined frequency and a dummy character), and pushes that new node back into the priority queue. This process effectively builds the Huffman Tree from the bottom up, ensuring that characters with lower frequencies end up deeper in the tree (and thus have longer codes), while characters with higher frequencies are closer to the root (and have shorter codes). The time complexity of this loop is O(M log M) in total, where M is the number of unique characters, because each merge operation involves popping two nodes and pushing one node back into the priority queue, and there are M-1 merge operations in total.
        while (pq.size() > 1) {

            // Pop the two nodes with lowest frequency
            HuffmanNode* left  = pq.top(); pq.pop();
            HuffmanNode* right = pq.top(); pq.pop();
            // top() and pop() are member functions of the priority_queue class in C++. top() returns a reference to the top element of the priority queue (the element with the highest priority, which in our case is the node with the lowest frequency due to our custom comparator). pop() removes the top element from the priority queue. In this code, we first call pq.top() to get the node with the lowest frequency and store it in left, then call pq.pop() to remove that node from the priority queue. We repeat this process to get the second lowest frequency node and store it in right. This allows us to access and remove the two nodes with the smallest frequencies for merging.

            //--------------------------------------------
            // Create a new internal node with combined frequency
            // '$' is just a placeholder — internal nodes don't hold real chars
            int combinedFreq = left->freq + right->freq;
            HuffmanNode* merged = new HuffmanNode('$', combinedFreq);
            merged->left  = left;
            merged->right = right;

            // Push the merged node back into the heap
            pq.push(merged);
        }

        // The last remaining node is the root of the full tree
        root = pq.top();
    }

    // ── PUBLIC: Print all Huffman Codes ──
    void printCodes() {
        if (root == nullptr) {
            cout << "Tree not built yet!" << endl;
            return;
        }

        // Map to store: character → binary string
        unordered_map<char, string> huffmanCode;

        // Kick off the recursive DFS from root with empty string
        encode(root, "", huffmanCode);

        // Print results
        cout << "Huffman Codes:\n";
        cout << "──────────────\n";
        for (auto& pair : huffmanCode) {
            cout << pair.first << " : " << pair.second << endl;     // pair.first is the character, pair.second is the corresponding Huffman code (binary string) for that character. The loop iterates through each key-value pair in the huffmanCode map and prints the character along with its Huffman code in a formatted manner.
        }
    }

    // ── PUBLIC: Compress a string → binary string ──
    // Converts each character to its Huffman code and concatenates.
    // Returns the full binary string e.g. "000100110..."
    // This demonstrates the variable-length encoding — frequent chars
    // get shorter codes, so the total bit count is less than fixed 8-bit ASCII.
    string compress(const string& text) {
        if (root == nullptr) {
            cout << "Tree not built yet!" << endl;
            return "";
        }

        // Build the char → code map using the same DFS encode helper
        unordered_map<char, string> huffmanCode;
        encode(root, "", huffmanCode);

        // Replace each character with its Huffman binary code
        // e.g. 'a' → "010", ' ' → "101", etc.
        string compressed = "";
        for (char ch : text) {
            compressed += huffmanCode[ch]; // append the binary code for each char
        }

        return compressed;
    }

    // ── PUBLIC: Decode ──
    // Takes a binary string (e.g. "000100110...") and walks the Huffman Tree
    // bit by bit to recover the original text.
    //
    // HOW IT WORKS:
    // Start at root. For every bit in the binary string:
    //   '0' → go left
    //   '1' → go right
    // When you hit a leaf node (both children are nullptr) → that's a character.
    // Append it to result, jump back to root, keep reading bits for next char.
    //
    // This works because Huffman codes have the PREFIX PROPERTY —
    // no code is a prefix of another, so there is never any ambiguity
    // about where one character ends and the next begins.
    // That is exactly why Huffman is LOSSLESS.
    string decode(const string& binaryStr) {
        if (root == nullptr) {
            cout << "Tree not built yet!" << endl;
            return "";
        }

        string result = "";
        HuffmanNode* curr = root; // pointer that walks the tree, reset to root after each char

        for (char bit : binaryStr) {

            // Walk left for '0', right for '1'
            if (bit == '0')
                curr = curr->left;
            else
                curr = curr->right;

            // Leaf node reached — no children means this is a real character
            if (!curr->left && !curr->right) {
                result += curr->data; // append the decoded character to result
                curr = root;          // reset back to root to decode the next character
            }
        }

        return result;
    }
};

// ─────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────
int main() {
    string text = "Huffman coding is a data compression algorithm.";

    // Create the Huffman Tree object
    HuffmanTree ht;

    // Step 1: Build the tree from the input text
    ht.build(text);

    // Step 2: Print each character's Huffman code
    ht.printCodes();

    // Step 3: Compress — convert original text to binary string
    string compressed = ht.compress(text);
    cout << "\nOriginal text  : " << text << endl;
    cout << "Original bits  : " << text.size() * 8 << " bits (ASCII 8-bit)" << endl;
    cout << "Compressed bits: " << compressed.size() << " bits (Huffman)" << endl;
    cout << "Binary string  : " << compressed.substr(0, 40) << "..." << endl;

    // Step 4: Decode — recover original text from binary string
    string decoded = ht.decode(compressed);
    cout << "\nDecoded text   : " << decoded << endl;

    // Step 5: Lossless check — decoded must exactly match original
    // If this prints PASSED, the prefix property is working correctly
    if (decoded == text)
        cout << "Lossless check : PASSED — original and decoded match!" << endl;
    else
        cout << "Lossless check : FAILED" << endl;

    return 0;
}

/*
    frequent chars = shorter codes — that is the entire point of Huffman coding
*/