/*
    A business house has several offices in different countries; they want to lease phone lines to connect them with
    each other and the phone company charges different rent to connect different pairs of cities. Business house wants
    to connect all its offices with a minimum total cost. Solve the problem using Prim’s algorithm.
*/

#include <iostream>
#include <string>
using namespace std;

#define inf 999

class graph{
    int cost[10][10];
    int n;
    string line = "===========================================================";

public:
    graph();
    void create();
    void display();
    void prims(int start_v);
};

graph :: graph(){
    cout << line <<endl;
    cout << "Enter the total number of cities: ";
    cin >> n;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cost[i][j] = inf;
        }
    }
}

void graph :: create(){
    char choice;
    int weight;

    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            cout << line <<endl;
            cout << "Is there an edge between City " << i << " and City " << j << "? (y/n): ";
            cin >> choice;

            if(choice == 'y' || choice == 'Y'){
                cout << line <<endl;
                cout << "Enter the cost: ";
                cin >> weight;

                cost[i][j] = weight;
                cost[j][i] = weight;
            }
        }
    }
}

void graph :: display(){
    cout << line <<endl;
    cout << "Adjacency Matrix:\n";

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << cost[i][j] << "\t";
        }
        cout << endl;
    }
}

void graph :: prims(int start_v){
    int nearest[10];
    int t[10][3];
    int mincost = 0;
    int r = 0;

    for(int i = 0; i < n; i++){
        nearest[i] = start_v;
    }

    nearest[start_v] = -1;

    for(int i = 0; i < n - 1; i++){
        int min = inf;
        int j = -1;

        for(int k = 0; k < n; k++){
            if(nearest[k] != -1 && cost[k][nearest[k]] < min){
                min = cost[k][nearest[k]];
                j = k;
            }
        }

        t[r][0] = nearest[j];
        t[r][1] = j;
        t[r][2] = min;
        r++;

        mincost += min;
        nearest[j] = -1;

        for(int k = 0; k < n; k++){
            if(nearest[k] != -1 && cost[k][nearest[k]] > cost[k][j])
                nearest[k] = j;
        }
    }

    cout << line <<endl;
    cout << "Edges in Minimum Spanning Tree:\n";
    for(int i = 0; i < r; i++)
        cout << t[i][0] << " -> " << t[i][1] << "  Cost: " << t[i][2] << endl;

    cout << line <<endl;
    cout << "\nMinimum Cost = " << mincost << endl;
    cout << line <<endl;
}

int main(){
    string line = "===========================================================";
    int start;
    graph g;
    g.create();
    g.display();

    cout << line <<endl;
    cout << "Enter the starting vertex for Prim's algorithm: ";
    cin >> start;

    g.prims(start);

    return 0;
}

