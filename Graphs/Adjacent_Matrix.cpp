#include <iostream>
using namespace std;

// ============================================================
// ADJACENCY MATRIX - FIXED & COMPLETE
// ============================================================
// BUGS FIXED:
// 1. insertVertexWithKey: 'v[vcount] = v' → was treating int as array
//    Fixed with a separate vertexKeys[] array
// 2. getEdgeCount(): was empty, now correctly counts edges
// 3. Added missing vertex key lookup for operations
// ============================================================

const int MAX_N = 6;

class AdjMatrix {
private:
    int arr[MAX_N][MAX_N];      // adjacency / weight matrix
    int vertexKeys[MAX_N];      // FIX: stores actual vertex values
    bool dir;
    bool weighted;
    int vcount;

    // Helper: find index of vertex value v
    int findIndex(int v) {
        for (int i = 0; i < vcount; i++)
            if (vertexKeys[i] == v) return i;
        return -1;
    }

public:
    AdjMatrix(bool directed = false, bool weight = false) {
        dir = directed;
        weighted = weight;
        vcount = 0;
        for (int i = 0; i < MAX_N; i++) {
            vertexKeys[i] = -1;
            for (int j = 0; j < MAX_N; j++)
                arr[i][j] = 0;
        }
    }

    bool isEmpty() {
        return (vcount == 0);
    }

    int getVertexCount() { return vcount; }

    // FIXED: was completely empty before
    int getEdgeCount() {
        int count = 0;
        for (int i = 0; i < vcount; i++)
            for (int j = 0; j < vcount; j++)
                if (arr[i][j] != 0) count++;
        return dir ? count : count / 2;
    }

    bool edgeExists(int v1, int v2) {
        int i1 = findIndex(v1);
        int i2 = findIndex(v2);
        if (i1 == -1 || i2 == -1) return false;
        return arr[i1][i2] != 0;
    }

    // FIXED: 'v[vcount] = v' was treating int v as array
    void insertVertex(int v) {
        if (vcount >= MAX_N) {
            cout << "Vertex limit reached.\n";
            return;
        }
        if (findIndex(v) != -1) {
            cout << "Vertex " << v << " already exists.\n";
            return;
        }
        vertexKeys[vcount] = v;
        vcount++;
    }

    // Supports both weighted and unweighted
    void insertEdge(int v1, int v2, int w = 1) {
        int i1 = findIndex(v1);
        int i2 = findIndex(v2);
        if (i1 == -1 || i2 == -1) {
            cout << "One or both vertices do not exist.\n";
            return;
        }
        arr[i1][i2] = w;
        if (!dir) arr[i2][i1] = w;
    }

    void deleteEdge(int v1, int v2) {
        int i1 = findIndex(v1);
        int i2 = findIndex(v2);
        if (i1 == -1 || i2 == -1) return;
        arr[i1][i2] = 0;
        if (!dir) arr[i2][i1] = 0;
    }

    void deleteVertex(int v) {
        int idx = findIndex(v);
        if (idx == -1) { cout << "Vertex not found.\n"; return; }

        // Shift rows and columns
        for (int i = idx; i < vcount - 1; i++) {
            vertexKeys[i] = vertexKeys[i + 1];
            for (int j = 0; j < vcount; j++)
                arr[i][j] = arr[i + 1][j];
        }
        for (int j = idx; j < vcount - 1; j++) {
            for (int i = 0; i < vcount - 1; i++)
                arr[i][j] = arr[i][j + 1];
        }
        // Clear last row/col
        for (int k = 0; k < MAX_N; k++) {
            arr[vcount - 1][k] = 0;
            arr[k][vcount - 1] = 0;
        }
        vertexKeys[vcount - 1] = -1;
        vcount--;
    }

    bool searchVertex(int v) { return findIndex(v) != -1; }

    int searchEdge(int v1, int v2) {
        int i1 = findIndex(v1);
        int i2 = findIndex(v2);
        if (i1 == -1 || i2 == -1) return 0;
        return arr[i1][i2];
    }

    void display() {
        cout << "\n--- Adjacency Matrix ---\n";
        cout << "   ";
        for (int i = 0; i < vcount; i++) cout << vertexKeys[i] << "  ";
        cout << endl;
        for (int i = 0; i < vcount; i++) {
            cout << vertexKeys[i] << "  ";
            for (int j = 0; j < vcount; j++)
                cout << arr[i][j] << "  ";
            cout << endl;
        }
    }
};

int main() {
    AdjMatrix g(false, false);  // undirected, unweighted

    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);

    g.insertEdge(1, 2);
    g.insertEdge(1, 3);
    g.insertEdge(2, 4);
    g.insertEdge(3, 4);

    g.display();
    cout << "Vertices: " << g.getVertexCount() << endl;
    cout << "Edges: "    << g.getEdgeCount()    << endl;
    cout << "Edge(1,2): " << (g.edgeExists(1, 2) ? "Yes" : "No") << endl;
    cout << "Edge(1,4): " << (g.edgeExists(1, 4) ? "Yes" : "No") << endl;

    cout << "\nDeleting vertex 3:\n";
    g.deleteVertex(3);
    g.display();

    system("pause>0");
    return 0;
}