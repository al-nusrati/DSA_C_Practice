#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
using namespace std;

class User {
public:
    string name;
    int    age;

    // constructor — called when you create a User object
    User(string n, int a) : name(n), age(a) {}

    // default constructor — needed so map can create empty slots
    User() : name(""), age(0) {}

    void display() {
        cout << name << " (age " << age << ")\n";
    }
};





class Network {
private:
    // container 1: name → actual User object
    unordered_map<string, User> users;

    // container 2: name → list of friend names
    unordered_map<string, vector<string>> adj;

public:










    // add a user — stores User object inside the map
    void addUser(string name, int age) {
        users[name] = User(name, age);   //User() is called to create object in map
        adj[name];                        // create empty adj list
    }

    // connect two users — only touches adj, not users
    void connect(string a, string b) {
        if (!users.count(a) || !users.count(b)) return;//count() checks if user exists in map
        adj[a].push_back(b);// pushes b into a's friend list, explanation: adj[a] returns vector<string> of a's friends, then push_back adds b to that vector
        adj[b].push_back(a);             // undirected
    }

    // display — pulls from BOTH containers
    void display() {
        for (auto& [name, user] : users) {//syntax explanation: iterates through each key-value pair in the users map, where 'name' is the key (string) and 'user' is the value (User object)`
            user.display();               // call User's method
            cout << "  friends: ";
            for (auto& f : adj[name])//adj[name] gives vector<string> of friends for this user, then we loop through that vector to print each friend's name
                cout << f << " ";
            cout << "\n";
        }
    }

    void BFS(string start) {
        if (!users.count(start)) return;

        unordered_set<string> visited;   //explanation: keeps track of which users we've already visited to avoid cycles, unordered_set allows O(1) average time complexity for insertions and lookups
        queue<string> q;    //explanation: standard queue for BFS, stores names of users to visit next

        visited.insert(start);//inserts the starting user's name into the visited set to mark it as visited
        q.push(start);// keeps track of which user to visit next, we start by pushing the starting user's name into the queue

        while (!q.empty()) {
            string curr = q.front(); q.pop();//dequeue the next user to visit, q.front() gives us the name of the user at the front of the queue, and q.pop() removes that name from the queue

            // use name to get full User object from users map
            users[curr].display();

            for (auto& neighbor : adj[curr]) {//this loop iterates through the friends of the current user, adj[curr] gives us the vector of friend names for the current user, and we loop through that vector to process each friend
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
    }

    vector<string> suggestFriends(string name) {
        unordered_set<string> direct(    adj[name].begin(), adj[name].end()); // create a set of direct friends for O(1) lookups, explanation: this line initializes an unordered_set called 'direct' with the friends of the user specified by 'name', adj[name] gives us the vector of friend names, and we use that vector to construct the unordered_set which allows for O(1) average time complexity when checking if someone is a direct friend
        vector<string> suggestions;

        for (auto& f : adj[name])           // loop friends
            for (auto& fof : adj[f])        // loop friends-of-friend
                if (fof != name && !direct.count(fof))// if not already a direct friend, and not self
                    suggestions.push_back(fof);// add to suggestions

        return suggestions;
    }



};

int main() {
    Network net;              // one manager — owns everything

    // add users (internally creates User objects + adj slots)
    net.addUser("Hasnain",  21);
    net.addUser("Ehtisham", 20);
    net.addUser("Farzad",   22);
    net.addUser("Abdur Rehman", 21);

    // connect (internally modifies adj on both sides)
    net.connect("Hasnain",  "Ehtisham");
    net.connect("Ehtisham", "Farzad");
    net.connect("Ehtisham", "Abdur Rehman");

    net.display();

    // BFS — uses queue + unordered_set internally
    net.BFS("Hasnain");//this will print Hasnain, then Ehtisham, then Farzad and Abdur Rehman, because Ehtisham is a direct friend of Hasnain, and Farzad and Abdur Rehman are friends of Ehtisham
    //BFS is a graph traversal algorithm that explores the neighbor nodes (friends) level by level, starting from the given user. It uses a queue to keep track of which user to visit next and an unordered_set to keep track of which users have already been visited to avoid cycles.

    // suggestions — uses unordered_set internally
    auto s = net.suggestFriends("Hasnain");
    for (auto& name : s) cout << name << "\n";

    return 0;
}


/* Tasks:





*/