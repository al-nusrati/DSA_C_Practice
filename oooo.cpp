#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Post {
public:
    int id;
    string content;
    int likes, comments, shares;
    string status;

    Post(string c, int a, string s = "") : id(a), content(c), likes(0), comments(0), shares(0), status(s        ) {}
    Post() : id(0), content(""), likes(0), comments(0), shares(0), status("") {}

    void display() {
        cout << "ID: " << id << " content: " << content << " cikes: " << likes << " comments: " << comments << " status: " << status << '\n';
    }
};

class User {
public:
    string name;
    int id, followers;

    User(string n, int a, int f = 0) : name(n), id(a), followers(f) {}
    User() : name(""), id(0), followers(0) {}

    void display() {
        cout << name << " " << id<<endl;
    }
};

class Network {
private:
    unordered_map<string, User> users; 
    unordered_map<int, Post>    posts;
    unordered_map<string, vector<string>> User_adj;//vector<string> is the list of friends for each user
    unordered_map<int, vector<int>> Post_adj;

public:
    void addPost(string content, int id) {
        posts[id] = Post(content, id);
        Post_adj[id];
    }

    void addUser(string name, int id) {
        users[name] = User(name, id);
        User_adj[name];
    }

    void connect(string a, string b) {
        if (!users.count(a) || !users.count(b)) return;//count() tells 
        User_adj[a].push_back(b);
        User_adj[b].push_back(a);
    }

    void linkPost(int a, int b){
        if (!posts.count(a) || !posts.count(b)) return;
        Post_adj[a].push_back(b);
        Post_adj[b].push_back(a);
    }

    void linkContenc(int userID, string s){
        int postID = userID;
        while (posts.count(postID)) {
            ++postID;
        }

        posts[postID] = Post(s, postID);
        Post_adj[postID];
    }

    void selectionSort_singlePass(vector<string> vec, int iStart, int iEnd) {
	int minIndex = iStart;
	// find index of smallest number in the range [iStart+1, iEnd]
	for (int i = iStart + 1; i <= iEnd; i++) {
		if (vec[i] < vec[minIndex]) {
			minIndex = i;
		}
	}
	// swap smallest number with the first number in the range
	swap(vec[iStart], vec[minIndex]);
}

    void display() {
        for (auto& [name, user] : users) {
            user.display();
            cout << "=>friends: ";
            for (auto& f : User_adj[name])
                cout << f << " ";
            cout << "\n";
        }
    }

    void search_Tag(int tag) {
        if (!posts.count(tag)) return;

        unordered_set<int> visited;
        queue<int> q;

        visited.insert(tag);
        q.push(tag);

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            posts[curr].display();

            for (int neighbor : Post_adj[curr]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
    }

    vector<string> suggestPosts(int id) {
        unordered_set<int> direct(Post_adj[id].begin(), Post_adj[id].end());
        vector<string> suggestions;

        for (int p : Post_adj[id])
            for (int pop : Post_adj[p])
                if (pop != id && !direct.count(pop))
                    suggestions.push_back(posts[pop].content);

        return suggestions;
    }

    vector<string> suggestFriends(const string& name) {
        if (!users.count(name)) return {};

        unordered_set<string> direct(User_adj[name].begin(), User_adj[name].end());
        vector<string> suggestions;

        for (const auto& frnd : User_adj[name])
            for (const auto& fof : User_adj[frnd])
                if (fof != name && !direct.count(fof))
                    suggestions.push_back(fof);

        return suggestions;
    }
};

int main() {
    Network net;
 
    net.addUser("Jawad",  21);
    net.addUser("Ahmed",  20);
    net.addUser("Usaed",   22);
    net.addUser("Shazil", 21);

    net.addPost("This is by jawad", 101);
    net.addPost("This is by ahmed", 102);

    net.connect("Jawad", "Ahmed");
    net.connect("Ahmed", "Shazil");
    net.connect("Ahmed", "Usaed");
    net.linkPost(102, 101);

    net.linkContenc(21, "Im jawad");

    net.display();
    net.search_Tag(101);


    vector<string> s = net.suggestFriends("Jawad");
    for (auto& name : s) 
        cout << name << "\n";

    return 0;
}