#include <iostream>
#include <list>
#include <string>
using namespace std;

class HashMap {
private:
    static const int hashIndexes = 10;
    list<pair<int, string>> ArrLinkedList[hashIndexes];  //array of linked lists 

    int hashFunction(int key) {
        return key % hashIndexes;
    }

public:

    void insert(int key, string value) {
        int index = hashFunction(key);
        for (auto it = ArrLinkedList[index].begin(); it != ArrLinkedList[index].end(); it++) {
            if (it->first == key) {    //this checks if key already exists or not. if it does then it updates 'value' of that 'key'.
                it->second = value;
                cout << "Key " << key << " updated to " << value << "\n";
                return; 
            }
        }
        ArrLinkedList[index].push_back({key, value});   //this is add new key value pair to the end of the linked list at that index.
        cout << "Inserted (" << key << ", " << value << ") at index " << index << "\n";
    }

    void deleteItem(int key) {
        int index = hashFunction(key);
        for (auto it = ArrLinkedList[index].begin(); it != ArrLinkedList[index].end(); it++) {      //no array , used iterator to traverse the linked list at that index as memory is scattered
            if (it->first == key) {
                ArrLinkedList[index].erase(it); // i. deletes ii. shifts the rest of the elements in the linked list to fill the gap left iii. frees the memory of the deleted node.
                cout << "Key " << key << " deleted.\n";
                return;
            }
        }
        cout << "Key " << key << " not found. Nothing deleted.\n";
    }

    void search(int key) {
        int index = hashFunction(key);
        for (auto it = ArrLinkedList[index].begin(); it != ArrLinkedList[index].end(); it++) {
            if (it->first == key) {
                cout << "Found: Key " << key << " " << it->second << " at index " << index << "\n";
                return;
            }
        }
        cout << "Key " << key << " not found.\n";
    }

    void display() {
        cout << "\n--- Hash Table State ---\n";
        for (int i = 0; i < hashIndexes; i++) {
            cout << "Bucket [" << i << "]: ";
            if (ArrLinkedList[i].empty()) {
                cout << "empty";
            } else {
                for (auto& pair : ArrLinkedList[i]) {
                    cout << "(" << pair.first << ", " << pair.second << ") -> ";
                }
                cout << "NULL";
            }
            cout << "\n";
        }
    }

        bool isEmpty() {
        for (int i = 0; i < hashIndexes; i++) { //iterating through all indexes of the hash array
            if (!ArrLinkedList[i].empty()) {
                return false;
            }
        }
        return true;
    }   

};

int main() {
    HashMap hm;

    hm.insert(105, "Jawad");
    hm.insert(205, "Rujman");   // Collision
    hm.insert(305, "Raiyan");   
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