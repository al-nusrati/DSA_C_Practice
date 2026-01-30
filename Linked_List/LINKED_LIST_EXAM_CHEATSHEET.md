# LINKED LIST EXAM CHEAT SHEET
## Universal Approach for Exams & Quizzes

---

## 1. BASIC STRUCTURE (ALWAYS START HERE)

```cpp
template <typename T>
struct node {
    T data;
    node<T>* next;
};

template <typename T>
class linkedList {
private:
    node<T>* head;
    node<T>* tail;  // IMPORTANT: Makes insertAtEnd O(1)
    
public:
    linkedList() : head(NULL), tail(NULL) {}
    ~linkedList() { freeMemory(); }
};
```

**KEY EXAM POINTS:**
- Template = works with ANY type (int, string, struct)
- `head` = first node
- `tail` = last node (optional but saves time)
- Always initialize both to NULL

---

## 2. INSERTION PATTERNS

### **A) Insert at Beginning - O(1)**
```cpp
void insertAtBeginning(T val) {
    node<T>* newNode = new node<T>;
    newNode->data = val;
    newNode->next = head;  // New points to old head
    head = newNode;        // Update head
    
    if(tail == NULL) {     // CRITICAL: Empty list case
        tail = head;
    }
}
```

**EXAM TRICK:** 
- **3 steps:** Create → Point to old head → Update head
- **Edge case:** Empty list (when tail is NULL)

**Drawing for exam:**
```
Before: head → [5] → [3] → NULL
Insert 7:
Step 1: [7] created
Step 2: [7] → [5] → [3] → NULL
Step 3: head → [7] → [5] → [3] → NULL
```

---

### **B) Insert at End - O(1) with tail**
```cpp
void insertAtEnd(T val) {
    node<T>* newNode = new node<T>;
    newNode->data = val;
    newNode->next = NULL;
    
    if(head == NULL) {     // CRITICAL: Empty list
        head = tail = newNode;
        return;
    }
    
    tail->next = newNode;  // Old tail points to new
    tail = newNode;        // Update tail
}
```

**EXAM TRICK:**
- **WITHOUT tail:** Must traverse entire list = O(n)
- **WITH tail:** Direct access = O(1)
- **Edge case:** Empty list (head == NULL)

---

### **C) Insert at Position - O(n)**
```cpp
void insertAtAnyPos(int position, T val) {
    // Edge case 1: Insert at start
    if(position == 0 || position == 1) {
        insertAtBeginning(val);
        return;
    }
    
    // Traverse to position-1
    node<T>* temp = head;
    for(int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    
    // Validation
    if(temp == NULL) {
        cout << "Invalid position!" << endl;
        return;
    }
    
    // Insert
    node<T>* newNode = new node<T>;
    newNode->data = val;
    newNode->next = temp->next;  // New points to next
    temp->next = newNode;        // Previous points to new
    
    // Edge case 2: Inserted at end
    if(newNode->next == NULL) {
        tail = newNode;
    }
}
```

**EXAM TRICK:**
- **Stop at (position - 1)** not position!
- Why? You need the node BEFORE insertion point
- **Don't forget:** Update tail if inserted at end

**Drawing for exam:**
```
Insert 99 at position 3:
Before: head → [1] → [2] → [3] → NULL
                     ↑
                  (pos-1)
After:  head → [1] → [2] → [99] → [3] → NULL
```

---

## 3. DELETION PATTERNS

### **A) Delete from Start - O(1)**
```cpp
void deleteFromStart() {
    if(head == NULL) {        // CRITICAL: Empty check
        return;
    }
    
    node<T>* temp = head;     // Save old head
    head = head->next;        // Move head forward
    delete temp;              // Free memory
    
    if(head == NULL) {        // CRITICAL: List became empty
        tail = NULL;
    }
}
```

**EXAM TRICK:**
- **3 steps:** Save → Move → Delete
- **Edge case:** List becomes empty (update tail)
- **Memory leak:** MUST use `delete`

---

### **B) Delete from End - O(n)**
```cpp
void deleteFromEnd() {
    if(head == NULL) return;  // Empty list
    
    // Only one node
    if(head->next == NULL) {
        delete head;
        head = tail = NULL;
        return;
    }
    
    // Find second-to-last node
    node<T>* temp = head;
    while(temp->next->next != NULL) {  // traverse & Stop at 2nd last
        temp = temp->next;
    }
    
    delete temp->next;        // Delete last
    temp->next = NULL;        // Break link
    tail = temp;              // Update tail
}
``` 

**EXAM TRICK:**
- **Key:** Must reach **SECOND-TO-LAST** node
- **Why?** Need to set its `next` to NULL
- **Loop condition:** `temp->next->next != NULL`
- **Edge cases:** Empty list, single node

**Drawing:**
```
Before: head → [1] → [2] → [3] → NULL
                     ↑      ↑
                  2nd-last last
After:  head → [1] → [2] → NULL (tail)
```

---

### **C) Delete at Position - O(n)**
```cpp
void deleteAtAnyPos(int position) {
    if(head == NULL) return;
    
    // Edge case: Delete first
    if(position == 1) {
        deleteFromStart();
        return;
    }
    
    // Find node at (position - 1)
    node<T>* temp = head;
    for(int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    
    // Validation
    if(temp == NULL || temp->next == NULL) {
        return;
    }
    
    // Delete
    node<T>* toDelete = temp->next;
    temp->next = toDelete->next;  // Skip the node
    
    // Edge case: Deleted last node
    if(temp->next == NULL) {
        tail = temp;
    }
    
    delete toDelete;
}
```

**EXAM TRICK:**
- **Stop at (position - 1)** again!
- **Pattern:** temp → [DELETE THIS] → temp->next
- **Don't forget:** Update tail if deleted last

---

## 4. TRAVERSAL & UTILITY

### **A) Display (Forward)**
```cpp
void traverseForward() {
    node<T>* temp = head;
    while(temp != NULL) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}
```

**EXAM PATTERN:** Start at head, print while moving

---

### **B) Display (Reverse) - Uses Recursion**
```cpp
void traverseReverseHelper(node<T>* n) {
    if(n == NULL) return;
    
    traverseReverseHelper(n->next);  // Go to end first
    cout << n->data << " -> ";       // Print on way back
}

void traverseReverse() {
    traverseReverseHelper(head);
    cout << "NULL" << endl;
}
```

**EXAM TRICK:**
- **Recursion:** Go deep, print while returning
- **Alternative:** Use a stack (iterative)

---

### **C) Reverse List - O(n)**
```cpp
void reverse() {
    if(head == NULL || head->next == NULL) return;
    
    node<T>* prev = NULL;
    node<T>* current = head;
    node<T>* next = NULL;
    
    tail = head;  // CRITICAL: Old head becomes tail
    
    while(current != NULL) {
        next = current->next;    // Save next
        current->next = prev;    // Reverse link
        prev = current;          // Move prev forward
        current = next;          // Move current forward
    }
    
    head = prev;  // New head
}
```

**EXAM TRICK - MOST ASKED:**
- **3 pointers:** prev, current, next
- **Pattern:** Save → Reverse → Move
- **Don't forget:** Swap head and tail

**Drawing (MEMORIZE THIS):**
```
Before: head → [1] → [2] → [3] → NULL

Step by step:
prev=NULL, curr=[1], next=[2]
  NULL ← [1]   [2] → [3] → NULL
  
prev=[1], curr=[2], next=[3]
  NULL ← [1] ← [2]   [3] → NULL
  
prev=[2], curr=[3], next=NULL
  NULL ← [1] ← [2] ← [3]
  
After: head → [3] → [2] → [1] → NULL (tail)
```

---

### **D) Find Middle (Two Pointer)**
```cpp
void findMiddle() {
    if(head == NULL) return;
    
    node<T>* slow = head;
    node<T>* fast = head;
    
    while(fast != NULL && fast->next != NULL) {
        slow = slow->next;        // Move 1 step
        fast = fast->next->next;  // Move 2 steps
    }
    
    cout << "Middle: " << slow->data << endl;
}
```

**EXAM TRICK:**
- **Slow moves 1, Fast moves 2**
- When fast reaches end, slow is at middle
- **Works for even & odd length lists**

---

### **E) Count Nodes**
```cpp
int nodeCount() {
    int count = 0;
    node<T>* temp = head;
    while(temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}
```

---

### **F) Search**
```cpp
bool searchData(T val) {
    node<T>* temp = head;
    while(temp != NULL) {
        if(temp->data == val) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}
```

---

### **G) Get Nth Node**
```cpp
T getNthNode(int n) {
    node<T>* temp = head;
    for(int i = 1; i < n && temp != NULL; i++) {
        temp = temp->next;
    }
    
    if(temp == NULL) {
        // Handle error
        return T();  // Return default value
    }
    return temp->data;
}
```

---

## 5. SPECIAL FUNCTIONS

### **A) Copy Constructor (Deep Copy)**
```cpp
linkedList(const linkedList& other) {
    head = NULL;
    tail = NULL;
    
    node<T>* temp = other.head;
    while(temp != NULL) {
        insertAtEnd(temp->data);  // Copy each node
        temp = temp->next;
    }
}
```

**EXAM POINT:** Creates independent copy, not just pointer copy

---

### **B) Destructor (Free Memory)**
```cpp
~linkedList() {
    node<T>* temp;
    while(head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
    tail = NULL;
}
```

**EXAM POINT:** Prevents memory leaks

---

## 6. COMMON EXAM QUESTIONS

### **Q1: Detect Loop/Cycle**
```cpp
bool hasLoop() {
    node<T>* slow = head;
    node<T>* fast = head;
    
    while(fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        
        if(slow == fast) {
            return true;  // Loop found
        }
    }
    return false;
}
```

---

### **Q2: Remove Duplicates (Sorted List)**
```cpp
void removeDuplicates() {
    node<T>* current = head;
    
    while(current != NULL && current->next != NULL) {
        if(current->data == current->next->data) {
            node<T>* temp = current->next;
            current->next = temp->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
}
```

---

### **Q3: Merge Two Sorted Lists**
```cpp
linkedList<T> mergeSorted(linkedList<T>& other) {
    linkedList<T> result;
    node<T>* p1 = this->head;
    node<T>* p2 = other.head;
    
    while(p1 != NULL && p2 != NULL) {
        if(p1->data < p2->data) {
            result.insertAtEnd(p1->data);
            p1 = p1->next;
        } else {
            result.insertAtEnd(p2->data);
            p2 = p2->next;
        }
    }
    
    // Add remaining
    while(p1 != NULL) {
        result.insertAtEnd(p1->data);
        p1 = p1->next;
    }
    while(p2 != NULL) {
        result.insertAtEnd(p2->data);
        p2 = p2->next;
    }
    
    return result;
}
```

---

## 7. TIME COMPLEXITY (MEMORIZE)

| Operation | Without Tail | With Tail |
|-----------|--------------|-----------|
| Insert at Start | O(1) | O(1) |
| Insert at End | O(n) | **O(1)** |
| Insert at Position | O(n) | O(n) |
| Delete from Start | O(1) | O(1) |
| Delete from End | O(n) | O(n) |
| Delete at Position | O(n) | O(n) |
| Search | O(n) | O(n) |
| Reverse | O(n) | O(n) |
| Find Middle | O(n) | O(n) |

---

## 8. CRITICAL EDGE CASES (ALWAYS CHECK)

1. **Empty List** (head == NULL)
2. **Single Node** (head->next == NULL)
3. **Insert/Delete at Start**
4. **Insert/Delete at End**
5. **Invalid Position** (out of bounds)
6. **Update tail** when needed

---

## 9. TAIL POINTER RULES

**When to Update Tail:**

✅ **Insert at End:** `tail = newNode`
✅ **Insert at Beginning (empty list):** `tail = head`
✅ **Insert at Position (if at end):** `tail = newNode`
✅ **Delete from End:** `tail = second_last_node`
✅ **Delete from Start (list becomes empty):** `tail = NULL`
✅ **Delete at Position (if last node):** `tail = previous_node`

---

## 10. COMMON EXAM MISTAKES

❌ **Forgetting to update tail**
❌ **Off-by-one errors** (stopping at wrong position)
❌ **Memory leaks** (not using `delete`)
❌ **Not checking NULL** (causing crashes)
❌ **Wrong loop condition** (temp->next->next)

---

## 11. QUICK REFERENCE TEMPLATE

```cpp
#include <iostream>
using namespace std;

template <typename T>
struct node {
    T data;
    node<T>* next;
};

template <typename T>
class linkedList {
private:
    node<T>* head;
    node<T>* tail;
    
public:
    linkedList() : head(NULL), tail(NULL) {}
    
    ~linkedList() {
        while(head != NULL) {
            node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    // Add all methods here...
};
```

---

## 12. EXAM STRATEGY

1. **Draw the list** before coding
2. **Identify edge cases** first
3. **Use temp pointers** generously
4. **Don't forget `delete`** for memory
5. **Update tail** when needed
6. **Test with:** Empty list, 1 node, 2 nodes

---

## 13. POSITION INDEXING (IMPORTANT)

**In your code, position starts at:**
- **Position 0 or 1?** → Check your professor's convention
- **Your code uses:** 1-based indexing (position 1 = first node)

**Common patterns:**
```cpp
// To insert at position N: stop at (N-1)
for(int i = 1; i < position - 1; i++)

// To delete at position N: stop at (N-1)
for(int i = 1; i < position - 1; i++)

// To get Nth node: loop (N-1) times
for(int i = 1; i < n; i++)
```

---

## BONUS: PRIORITY INSERTION (Like Task 3)

```cpp
// Insert based on priority (smaller = higher priority)
void insertByPriority(T val, int priority) {
    node<T>* newNode = new node<T>;
    newNode->data = val;
    newNode->priority = priority;
    
    // Insert at start if higher priority than head
    if(head == NULL || priority < head->priority) {
        newNode->next = head;
        head = newNode;
        if(tail == NULL) tail = head;
        return;
    }
    
    // Find position
    node<T>* temp = head;
    while(temp->next != NULL && temp->next->priority <= priority) {
        temp = temp->next;
    }
    
    newNode->next = temp->next;
    temp->next = newNode;
    
    if(newNode->next == NULL) tail = newNode;
}
```

---

**FINAL TIP:** Practice drawing on paper! Visual understanding beats memorization.
