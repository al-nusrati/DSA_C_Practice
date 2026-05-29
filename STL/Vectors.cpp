#include <iostream>
#include <vector>
using namespace std;

void printVec(vector<int> &v){
    cout << "size: " << v.size() << endl;
    for (int i = 0; i< v.size(); i++){
        cout << v[i] << " ";
    }
    v.push_back(5);
    cout << endl;
}

void NprintVec(vector<pair<int, int>> &v){
    cout << "size: " << v.size() << endl;
    for (int i = 0; i< v.size(); i++){
        cout << v[i].first << " " << v[i].second << endl;
    }
    v.push_back({4,5});
    cout << endl;
}

int main(){

    int a[10];
    vector<int> v;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        v.push_back(x);
    }
    printVec(v);

    vector<int> v1(10);     // initializes vector with 10 values of 0 {0,0,0,0,0,0,0,0,0,0}
    vector<int> v2(5, 3);   // initializes v2 with 5 values of 3 {3,3,3,3,3} -- size = 5
    v2.push_back(7);        // v2 = {3 ,3 ,3 ,3 ,3 ,7}  -- size = 6     ---  O(1)
    v2.pop_back();          // v2 = {3 ,3 ,3 ,3 ,3}  --- size = 5   ---  O(1)

    vector<int> v3 = v;     // Copy || change in v wont change v3 || O(n)
    
    printVec(v);
    printVec(v);
    printVec(v2); 

    //==================================
    //  Nested Vectors
    //==================================

    vector<pair<int, int>> vec = {{1, 2}, {2, 3}, {3, 4}};
    NprintVec(vec);

    //==================================
    //  Array Vectors
    //==================================

    vector<int> vArray[3];   // this creates 3 vectors.
    for (int i = 0; i < 3; i++) {               //-------->>>   Iterating throufh ARRAY of VECTORS
        int n;
        cout << "Enter size for vector index " << i << ": ";
        cin >> n;
        
        for (int j = 0; j < n; j++) {           //--------->>>  Iterating through Vectors in side of array
            int x;
            cin >> x;
            vArray[i].push_back(x); 
        }
        /*
        *   vArray[0] = {1, 2, 3, 4}  :: n=4
        *   vArray[1] = {1, 2, 3, 4, 5, 6, 7}  :: n=7
        *   vArray[2] = {1, 2}  :: n=2
        */
    }
    cout << "\n--- Your Array of Vectors ---" << endl;
    for (int i = 0; i <3; i++) {
        cout << "v[" << i << "]: ";
        for (int j = 0; j < vArray[i].size(); j++) {
            cout << vArray[i][j] << " ";
        }
        cout << endl;
    }
}