#include <iostream>
#include <string>
#include <list>
#include <utility>      // for std::pair

using namespace std;

// ─── HASHMAP using std::list ───────────────────────
class HashMap {
private:
    static const int TABLE_SIZE = 10;
    
    // Each bucket is a list of key-value pairs
    list<pair<int, string>> buckets[TABLE_SIZE];

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    void insert(int key, string value) {
        int index = hashFunction(key);
        auto& bucket = buckets[index];

        cout << "-> Bucket[" << index << "] : ";

        // Search if key already exists → update
        for (auto& p : bucket) {
            if (p.first == key) {
                p.second = value;
                cout << "Updated key " << key << " -> " << value << "\n";
                return;
            }
        }

        // Key not found → insert new pair at front
        bucket.emplace_front(key, value);
        cout << "Inserted (" << key << ", " << value << ")\n";
    }

    void search(int key) {
        int index = hashFunction(key);
        const auto& bucket = buckets[index];

        for (const auto& p : bucket) {
            if (p.first == key) {
                cout << "FOUND: Key=" << key 
                     << " Value=" << p.second 
                     << " at Bucket[" << index << "]\n";
                return;
            }
        }
        cout << "NOT FOUND: Key=" << key << "\n";
    }

    void deleteItem(int key) {
        int index = hashFunction(key);
        auto& bucket = buckets[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                cout << "DELETED: Key=" << key 
                     << " from Bucket[" << index << "]\n";
                return;
            }
        }
        cout << "NOT FOUND: Key=" << key 
             << " — nothing deleted\n";
    }

    void display() {
        cout << "\n=== HashMap State ===\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Bucket[" << i << "]: ";
            
            if (buckets[i].empty()) {
                cout << "empty";
            } else {
                for (const auto& p : buckets[i]) {
                    cout << "(" << p.first << ", " << p.second << ") -> ";
                }
                cout << "NULL";
            }
            cout << "\n";
        }
        cout << "====================\n";
    }

    bool isEmpty() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (!buckets[i].empty()) 
                return false;
        }
        return true;
    }
};

// ─── MAIN ──────────────────────────────────────────
int main() {
    HashMap hm;

    hm.insert(105, "Jawad");
    hm.insert(205, "Rujman");   // collision with 105
    hm.insert(305, "Raiyan");   // collision again
    hm.insert(42,  "Musab");
    hm.insert(73,  "Ahmed");

    hm.display();

    hm.search(205);
    hm.search(99);

    hm.deleteItem(205);
    hm.search(205);

    hm.display();

    return 0;
}