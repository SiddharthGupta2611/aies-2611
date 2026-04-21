/*
    consider a  friend's network on facebook social website. Model it as a graph to represent each node as a user and a
    link to represent the friend relationship between them using adjancey list representation and perform DFS & BFS 
    traversal.
    a. create the graph using Adjancey list(friend name, id)
    b. display the graph
    c. perfrom the recur & non-recur traversal using DFS(using id)
    d. perform the non-recur traversal using BFS(using id)
*/

#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

class usernode {
public:
    int id;
    string name;
    int vertex;
    usernode *next;
};

class facebook {
private:
    usernode *head[50];
    int n;
    bool visited[50];
   
public:
    facebook() {
        n = 0;
        for(int i = 0; i < 50; i++) {
            head[i] = NULL;
        }
    }
   
    void Accept() {
        cout << "Number of vertices: ";
        cin >> n;
        cin.ignore();
        for(int i = 0; i < n; i++) {
            head[i] = new usernode;
            head[i]->id = i;
            head[i]->vertex = i;
            head[i]->next = NULL;
            cout << "Enter name for ID " << i << ": ";
            getline(cin, head[i]->name);
        }
    }
   
    void Create() {
        int v;
        char ans;
        usernode *temp, *curr;
   
        for(int i = 0; i < n; i++) {
            temp = head[i];
            cout << "\nFor vertex " << i << " (" << head[i]->name << ")" << endl;
            do {
                cout << "Enter adjacent vertex: ";
                cin >> v;
                if(v == i) {
                    cout << "Self loop not allowed" << endl;
                } else if(v >= 0 && v < n) {
                    curr = new usernode;
                    curr->vertex = v;
                    curr->id = v;
                    curr->next = NULL;
                    // Store friend name in adjacency list nodes
                    curr->name = head[v]->name;
                    temp->next = curr;
                    temp = temp->next;
                    cout << "Edge " << i << "->" << v << " added" << endl;
                } else {
                    cout << "Invalid vertex!" << endl;
                }
                cout << "Add more edges? (y/n): ";
                cin >> ans;
                cin.ignore();
            } while(ans == 'y' || ans == 'Y');
        }
    }
   
    void display() {
        cout << "\nGraph representation (Adjacency List):" << endl;
        for(int i = 0; i < n; i++) {
            cout << "(" << head[i]->id << ", " << head[i]->name << ")" << ": ";
            usernode *temp = head[i]->next;
            bool first = true;
            while(temp != NULL) {
                if(!first) cout << " -> ";
                cout << "(" << temp->id << ", " << temp->name << ")";
                first = false;
                temp = temp->next;
            }
            cout << endl;
        }
    }
   
    void resetVisited() {
        for(int i = 0; i < n; i++) {
            visited[i] = false;
        }
    }
   
    void getAdjacent(int v, int adj[]) {
        int idx = 0;
        usernode *temp = head[v]->next;
        while(temp != NULL) {
            adj[idx++] = temp->vertex;
            temp = temp->next;
        }
        adj[idx] = -1;
    }
   
    void DFS_Rec(int start) {
        cout << "\nDFS Recursive starting from " << start << ": ";
        resetVisited();
        DFS(start);
    }
   
    void DFS(int v) {
        visited[v] = true;
        cout << v << " ";
        int adj[50];
        getAdjacent(v, adj);
        for(int i = 0; adj[i] != -1; i++) {
            if(!visited[adj[i]]) {
                DFS(adj[i]);
            }
        }
    }
   
    void DFS_NonRec(int start) {
        cout << "\nDFS Non-Recursive starting from " << start << ": ";
        resetVisited();
        stack<int> s;
        s.push(start);
        visited[start] = true;
       
        while(!s.empty()) {
            int v = s.top();
            s.pop();
            cout << v << " ";
            int adj[50];
            getAdjacent(v, adj);
            for(int i = 0; adj[i] != -1; i++) {
                if(!visited[adj[i]]) {
                    s.push(adj[i]);
                    visited[adj[i]] = true;
                }
            }
        }
    }
   
    void BFS_NonRec(int start) {
        cout << "\nBFS starting from " << start << ": ";
        resetVisited();
        queue<int> q;
        q.push(start);
        visited[start] = true;
       
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";
            int adj[50];
            getAdjacent(v, adj);
            for(int i = 0; adj[i] != -1; i++) {
                if(!visited[adj[i]]) {
                    q.push(adj[i]);
                    visited[adj[i]] = true;
                }
            }
        }
    }
   
    ~facebook() {
        for(int i = 0; i < n; i++) {
            usernode *temp = head[i];
            while(temp != NULL) {
                usernode *next = temp->next;
                delete temp;
                temp = next;
            }
        }
    }
};

int main() {
    facebook f;
    int choice, start;
    f.Accept();
    f.Create();

    while(true) {
        cout << "\n=== Facebook Friend Network ===" << endl;
        cout << "1. Display Graph" << endl;
        cout << "2. DFS Recursive" << endl;
        cout << "3. DFS Non-Recursive" << endl;
        cout << "4. BFS Non-Recursive" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
       
        switch(choice) {
            case 1: f.display();
                    break;
            case 2: cout << "Enter starting vertex: ";
                    cin >> start;
                    f.DFS_Rec(start);
                    break;
            case 3: cout << "Enter starting vertex: ";
                    cin >> start;
                    f.DFS_NonRec(start);
                    break;
            case 4: cout << "Enter starting vertex: ";
                    cin >> start;
                    f.BFS_NonRec(start);
                    break;
            case 5: cout << "Exiting..." << endl;
                    return 0;
            default: cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
