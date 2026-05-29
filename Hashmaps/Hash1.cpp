#include <iostream>
#include <string>
using namespace std;

// ─── NODE of the linked list ───────────────────────
struct Node {
    int    key;
    string value;
    Node*  next;

    Node(int k, string v) : key(k), value(v), next(nullptr) {}
};

// ─── LINKED LIST (one per bucket) ──────────────────
struct LinkedList {
    Node* head;

    LinkedList() : head(nullptr) {}

    // INSERT or UPDATE
    void insert(int key, string value) {
        Node* current = head;

        // walk the chain — update if key exists
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                cout << "Updated key " << key << " -> " << value << "\n";
                return;
            }
            current = current->next;
        }

        // key not found → append new node at front (O(1))
        Node* newNode = new Node(key, value);
        newNode->next = head;
        head = newNode;
        cout << "Inserted (" << key << ", " << value << ")\n";
    }

    // SEARCH
    Node* search(int key) {
        Node* current = head;
        while (current != nullptr) {
            if (current->key == key) return current;
            current = current->next;
        }
        return nullptr;
    }

    // DELETE
    bool deleteNode(int key) {
        Node* current = head;
        Node* prev    = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr)        // deleting head
                    head = current->next;
                else
                    prev->next = current->next;

                delete current;
                return true;
            }
            prev    = current;
            current = current->next;
        }
        return false;
    }

    // DISPLAY one bucket
    void display() {
        Node* current = head;
        if (current == nullptr) { cout << "empty"; return; }
        while (current != nullptr) {
            cout << "(" << current->key << ", " << current->value << ") -> ";
            current = current->next;
        }
        cout << "NULL";
    }

    bool isEmpty() { return head == nullptr; }

    // destructor — free all nodes
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// ─── HASHMAP ───────────────────────────────────────
class HashMap {
private:
    static const int TABLE_SIZE = 10;
    LinkedList buckets[TABLE_SIZE];   // array of linked lists

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    void insert(int key, string value) {
        int index = hashFunction(key);
        cout << "-> Bucket[" << index << "] : ";
        buckets[index].insert(key, value);
    }

    void search(int key) {
        int index = hashFunction(key);
        Node* result = buckets[index].search(key);
        if (result)
            cout << "FOUND: Key=" << key << " Value=" << result->value
                << " at Bucket[" << index << "]\n";
        else
            cout << "NOT FOUND: Key=" << key << "\n";
    }

    void deleteItem(int key) {
        int index = hashFunction(key);
        if (buckets[index].deleteNode(key))
            cout << "DELETED: Key=" << key << " from Bucket[" << index << "]\n";
        else
            cout << "NOT FOUND: Key=" << key << " — nothing deleted\n";
    }

    void display() {
        cout << "\n=== HashMap State ===\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Bucket[" << i << "]: ";
            buckets[i].display();
            cout << "\n";
        }
        cout << "====================\n";
    }

    bool isEmpty() {
        for (int i = 0; i < TABLE_SIZE; i++)
            if (!buckets[i].isEmpty()) return false;
        return true;
    }
};

// ─── MAIN ──────────────────────────────────────────
int main() {
    HashMap hm;

    hm.insert(105, "Jawad");
    hm.insert(205, "Rujman");   // collision with 105 (both % 10 = 5)
    hm.insert(305, "Raiyan");   // collision again
    hm.insert(42,  "Musab");
    hm.insert(73,  "Ahmed");

    hm.display();

    hm.search(205);
    hm.search(99);

    hm.deleteItem(205);
    hm.search(205);

    hm.display();

    system("pause>0");
    return 0;
}