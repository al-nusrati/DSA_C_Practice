#include <iostream>
#include <string>
using namespace std;

// ==========================================
// TEMPLATED INPUT VALIDATION (Elite Tier)
// ==========================================
template <typename T>
T getValidInput(string prompt) {
    T value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        }
        cout << "Error: Invalid input! Please enter the correct data type.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

// --- 1. Node Structure (Chaining Bucket Node) ---
struct node {
    int data;
    node* next;
};

// --- 2. HashTable Class Definition ---
class HashTable {
private:
    static const int DEFAULT_SIZE = 10;
    node** table;       // Array of node pointers (each index = a bucket)
    int tableSize;
    int count;          // Total elements stored

    // ==========================================
    // PRIVATE HELPER FUNCTIONS (The Logic Core)
    // ==========================================

    // --- Hash Function (Division Method) ---
    int hashFunction(int key) {
        // Handles negative keys safely using modulo arithmetic
        return ((key % tableSize) + tableSize) % tableSize;
    }

    // --- Create a new chain node ---
    node* createNode(int val) {
        node* newNode = new node;
        newNode->data  = val;
        newNode->next  = nullptr;
        return newNode;
    }

    // --- Free an entire chain at a bucket ---
    void freeChain(node* head) {
        while (head) {
            node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // --- Internal Search (returns the node ptr for reuse) ---
    node* searchNode(int val) {
        int idx  = hashFunction(val);
        node* cur = table[idx];

        while (cur) {
            if (cur->data == val) return cur;   // Found
            cur = cur->next;
        }
        return nullptr;     // Not found
    }

public:
    // ==========================================
    // PUBLIC INTERFACE (Wrappers)
    // ==========================================

    // --- Constructor ---
    HashTable(int size = DEFAULT_SIZE) {
        tableSize = (size > 0) ? size : DEFAULT_SIZE;
        count     = 0;
        table     = new node*[tableSize];

        // Initialize all buckets to nullptr
        for (int i = 0; i < tableSize; i++)
            table[i] = nullptr;
    }

    // --- Destructor ---
    ~HashTable() {
        for (int i = 0; i < tableSize; i++)
            freeChain(table[i]);
        delete[] table;
        table = nullptr;
    }

    // ==========================================
    // CORE OPERATIONS
    // ==========================================

    // --- Insert ---
    void insert(int val) {
        // Reject duplicates (set semantics)
        if (searchNode(val)) {
            cout << "Warning: " << val << " already exists. Duplicates not allowed.\n";
            return;
        }

        int    idx     = hashFunction(val);
        node*  newNode = createNode(val);

        // Prepend to chain (O(1) insertion)
        newNode->next = table[idx];
        table[idx]    = newNode;
        count++;

        cout << "Inserted " << val << " at bucket [" << idx << "]\n";
    }

    // --- Delete ---
    bool remove(int val) {
        int    idx  = hashFunction(val);
        node*  cur  = table[idx];
        node*  prev = nullptr;

        while (cur) {
            if (cur->data == val) {
                // Unlink the node
                if (prev) prev->next = cur->next;    // Middle / Tail
                else       table[idx] = cur->next;   // Head of chain

                delete cur;
                count--;
                cout << "Deleted " << val << " from bucket [" << idx << "]\n";
                return true;
            }
            prev = cur;
            cur  = cur->next;
        }

        cout << "Delete failed: " << val << " not found.\n";
        return false;   // Element not found
    }

    // --- Search (Reusability fix: returns bool, printing done outside) ---
    bool search(int val) {
        return searchNode(val) != nullptr;
    }

    // --- isEmpty ---
    bool isEmpty() { return (count == 0); }

    // --- Display entire table with chains ---
    void display() {
        cout << "\n--- Hash Table (Size: " << tableSize
             << " | Elements: " << count << ") ---\n";

        for (int i = 0; i < tableSize; i++) {
            cout << "Bucket [" << i << "] -> ";

            if (!table[i]) {
                cout << "NULL\n";
                continue;
            }

            node* cur = table[i];
            while (cur) {
                cout << cur->data;
                if (cur->next) cout << " -> ";
                cur = cur->next;
            }
            cout << " -> NULL\n";
        }
        cout << endl;
    }
};

// ==========================================
// MAIN FUNCTION
// ==========================================
int main() {
    HashTable ht(7);    // Prime-sized table = better distribution

    cout << "========================================\n";
    cout << "       Hash Table ADT - Demo            \n";
    cout << "========================================\n";

    // --- Insertions ---
    cout << "\n--- Inserting Nodes ---\n";
    ht.insert(10);
    ht.insert(20);
    ht.insert(35);
    ht.insert(7);
    ht.insert(14);
    ht.insert(21);
    ht.insert(99);

    ht.display();

    // --- Collision Demonstration ---
    cout << "--- Inserting Collision Values (should chain) ---\n";
    ht.insert(28);   // 28 % 7 = 0, collides with 7 (7%7=0) and 21 (21%7=0)
    ht.display();

    // --- Duplicate Rejection ---
    cout << "--- Duplicate Rejection Test ---\n";
    ht.insert(10);   // Should warn and reject
    cout << endl;

    // --- Search ---
    cout << "--- Searching ---\n";
    if (ht.search(14))  cout << "Node 14  FOUND.\n";
    else                cout << "Node 14  NOT found.\n";

    if (ht.search(55))  cout << "Node 55  FOUND.\n";
    else                cout << "Node 55  NOT found.\n";
    cout << endl;

    // --- Deletion ---
    cout << "--- Deleting Nodes ---\n";
    ht.remove(21);          // Head of a chain
    ht.remove(28);          // Middle/tail of a chain
    ht.remove(999);         // Non-existent
    ht.display();

    // --- isEmpty Check ---
    cout << "--- isEmpty Check ---\n";
    cout << "Table is " << (ht.isEmpty() ? "EMPTY" : "NOT empty") << ".\n\n";

    // --- Interactive Input Test ---
    cout << "--- Interactive Input Test (Using Template) ---\n";
    int userVal = getValidInput<int>("Enter an integer to insert into Hash Table: ");
    ht.insert(userVal);

    if (ht.search(userVal))
        cout << "Confirmed: " << userVal << " is in the table.\n";

    ht.display();

    cout << "--- Destructor will run automatically here ---\n";

    system("pause>0");
    return 0;
}