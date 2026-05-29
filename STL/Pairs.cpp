#include <iostream>
using namespace std;

int main (){
    
    pair<int, string> p;
    //p = make_pair(101, "Jawad");
    p = {101, "Jawad"};
    cout << p.first << " " << p.second << endl;
    // .first && .second && make_pair( - , - ) || { - , - }

    pair<int, string> &p1 = p; // this makes a new name for pair p
    pair<int, string> p2 = p;  // this creates a copy of p
    p1.first = 3;
    cout << p.first << " " << p.second << endl;

    int a[] = {1, 2, 3};
    int b[] = {2, 3, 4};

    pair<int, int> p_array[3];
    p_array[0] = {1, 2};
    p_array[1] = {2, 3};
    p_array[2] = {3, 4};
    swap(p_array[0], p_array[2]);

    // printing pairs
    for (int i; i < 3; ++i)
    {
        cout << p_array[i].first << p_array[i] << endl;
    }

    // input
    cin >> p.first;
}