#include <iostream>
#include <string>
using namespace std;

// ============================================================
// ADJACENCY LIST - FIXED & COMPLETE
// ============================================================
// BUGS FIXED:
// 1. isEmpty() was returning vcount (int) instead of vcount==0
// 2. insertEdge() - entire function was broken / incomplete
// 3. deleteVertex() - incomplete, missing closing braces, broken logic
// 4. vCount typo fixed to vcount
// ============================================================

struct EdgeNode {
    int dest;
    EdgeNode* next;
    EdgeNode(int d) : dest(d), next(nullptr) {}
};

struct GNode {
    int vertex;
    EdgeNode* head;         // our own linked list (no STL)
    GNode() : vertex(-1), head(nullptr) {}
};

const int MAX_V = 10;

class AdjList {
private:
    GNode arr[MAX_V];
    bool dir;               // true = directed, false = undirected
    int vcount;

    // Helper: find array index of a vertex value. Returns -1 if not found.
    int findIndex(int v) {
        for (int i = 0; i < vcount; i++)
            if (arr[i].vertex == v) return i;
        return -1;
    }

    // Helper: add edge in adjacency list of vertex at index 'fromIdx' to 'toVal'
    void addEdge(int fromIdx, int toVal) {
        EdgeNode* newEdge = new EdgeNode(toVal);
        newEdge->next = arr[fromIdx].head;
        arr[fromIdx].head = newEdge;
    }

    // Helper: remove edge to 'toVal' from adjacency list at index 'fromIdx'
    void removeEdge(int fromIdx, int toVal) {
        EdgeNode* curr = arr[fromIdx].head;
        EdgeNode* prev = nullptr;
        while (curr) {
            if (curr->dest == toVal) {
                if (prev) prev->next = curr->next;
                else arr[fromIdx].head = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    // Helper: free all edge nodes of a GNode
    void freeEdgeList(int idx) {
        EdgeNode* curr = arr[idx].head;
        while (curr) {
            EdgeNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        arr[idx].head = nullptr;
    }

    // BFS helper using manual queue
    void bfsHelper(int startIdx, bool visited[]) {
        // Manual queue using array (bounded by vcount)
        int q[MAX_V];
        int front = 0, back = 0;

        visited[startIdx] = true;
        q[back++] = startIdx;

        while (front < back) {
            int curr = q[front++];
            cout << arr[curr].vertex << " ";

            EdgeNode* edge = arr[curr].head;
            while (edge) {
                int neighborIdx = findIndex(edge->dest);
                if (neighborIdx != -1 && !visited[neighborIdx]) {
                    visited[neighborIdx] = true;
                    q[back++] = neighborIdx;
                }
                edge = edge->next;
            }
        }
    }

    // DFS helper
    void dfsHelper(int idx, bool visited[]) {
        visited[idx] = true;
        cout << arr[idx].vertex << " ";

        EdgeNode* edge = arr[idx].head;
        while (edge) {
            int neighborIdx = findIndex(edge->dest);
            if (neighborIdx != -1 && !visited[neighborIdx])
                dfsHelper(neighborIdx, visited);
            edge = edge->next;
        }
    }

public:
    AdjList(bool directed = false) {
        dir = directed;
        vcount = 0;
    }

    ~AdjList() {
        for (int i = 0; i < vcount; i++)
            freeEdgeList(i);
    }

    // O(1) - fixed: was returning vcount (int) not bool
    bool isEmpty() { return (vcount == 0); }

    int getVertexCount() { return vcount; }

    int getEdgeCount() {
        int count = 0;
        for (int i = 0; i < vcount; i++) {
            EdgeNode* curr = arr[i].head;
            while (curr) { count++; curr = curr->next; }
        }
        return dir ? count : count / 2;
    }

    // O(V) check
    bool edgeExists(int v1, int v2) {
        int idx = findIndex(v1);
        if (idx == -1) return false;
        EdgeNode* curr = arr[idx].head;
        while (curr) {
            if (curr->dest == v2) return true;
            curr = curr->next;
        }
        return false;
    }

    void insertVertex(int v) {
        if (vcount >= MAX_V) {
            cout << "Vertex limit reached.\n";
            return;
        }
        if (findIndex(v) != -1) {
            cout << "Vertex " << v << " already exists.\n";
            return;
        }
        arr[vcount].vertex = v;
        arr[vcount].head = nullptr;
        vcount++;
    }

    // FIXED: was completely broken before
    void insertEdge(int v1, int v2) {
        int i1 = findIndex(v1);
        int i2 = findIndex(v2);
        if (i1 == -1 || i2 == -1) {
            cout << "One or both vertices do not exist.\n";
            return;
        }
        if (edgeExists(v1, v2)) {
            cout << "Edge already exists.\n";
            return;
        }
        addEdge(i1, v2);
        if (!dir) addEdge(i2, v1);  // undirected: add both directions
    }

    void deleteEdge(int v1, int v2) {
        int i1 = findIndex(v1);
        int i2 = findIndex(v2);
        if (i1 == -1 || i2 == -1) {
            cout << "One or both vertices do not exist.\n";
            return;
        }
        removeEdge(i1, v2);
        if (!dir) removeEdge(i2, v1);
    }

    // FIXED: was incomplete with missing braces and broken logic
    void deleteVertex(int v) {
        int idx = findIndex(v);
        if (idx == -1) {
            cout << "Vertex " << v << " not found.\n";
            return;
        }

        // Step 1: Remove all edges from OTHER vertices pointing TO v
        for (int i = 0; i < vcount; i++) {
            if (i != idx) removeEdge(i, v);
        }

        // Step 2: Free all edges FROM v
        freeEdgeList(idx);

        // Step 3: Shift array left to fill the gap
        for (int i = idx; i < vcount - 1; i++) {
            arr[i].vertex = arr[i + 1].vertex;
            arr[i].head   = arr[i + 1].head;
        }
        arr[vcount - 1].vertex = -1;
        arr[vcount - 1].head   = nullptr;
        vcount--;
    }

    int searchVertex(int v) { return findIndex(v); }

    void BFS(int startVertex) {
        int idx = findIndex(startVertex);
        if (idx == -1) { cout << "Vertex not found.\n"; return; }

        bool visited[MAX_V] = {};
        cout << "BFS from " << startVertex << ": ";
        bfsHelper(idx, visited);

        // Visit disconnected components
        for (int i = 0; i < vcount; i++)
            if (!visited[i]) bfsHelper(i, visited);
        cout << endl;
    }

    void DFS(int startVertex) {
        int idx = findIndex(startVertex);
        if (idx == -1) { cout << "Vertex not found.\n"; return; }

        bool visited[MAX_V] = {};
        cout << "DFS from " << startVertex << ": ";
        dfsHelper(idx, visited);

        for (int i = 0; i < vcount; i++)
            if (!visited[i]) dfsHelper(i, visited);
        cout << endl;
    }

    void display() {
        cout << "\n--- Adjacency List ---\n";
        for (int i = 0; i < vcount; i++) {
            cout << arr[i].vertex << " -> ";
            EdgeNode* curr = arr[i].head;
            while (curr) { cout << curr->dest << " -> "; curr = curr->next; }
            cout << "NULL\n";
        }
    }
};

int main() {
    AdjList g(false);   // undirected graph

    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);

    g.insertEdge(1, 2);
    g.insertEdge(1, 3);
    g.insertEdge(2, 4);
    g.insertEdge(3, 4);
    g.insertEdge(4, 5);

    g.display();
    cout << "Vertices: " << g.getVertexCount() << endl;
    cout << "Edges: "    << g.getEdgeCount()    << endl;
    cout << "Edge(1,2) exists: " << (g.edgeExists(1, 2) ? "Yes" : "No") << endl;
    cout << "Edge(1,5) exists: " << (g.edgeExists(1, 5) ? "Yes" : "No") << endl;

    g.BFS(1);
    g.DFS(1);

    cout << "\nDeleting vertex 3:\n";
    g.deleteVertex(3);
    g.display();

    system("pause>0");
    return 0;
}