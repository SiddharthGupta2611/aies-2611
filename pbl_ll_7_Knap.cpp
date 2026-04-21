//Implement 0/1 Knapsack OR Traveling Salesperson problem using Dynamic Programming

#include <iostream>
#include <string>
using namespace std;

class Knapsack {
public:
    int p;
    int w;
};

void Display(int B[101][101], int n, int W) {
    cout << "\nTable (rows: items 0-" << n << ", Cols: capacity 0-" << W << "): " << endl;
    cout << "\t";

    for (int c = 0; c <= W; c++) {
        cout << c << "\t";
    }
    cout << endl;

    for (int r = 0; r <= n; r++) {
        cout << r << "\t";
        for (int c = 0; c <= W; c++) {
            cout << B[r][c] << "\t";
        }
        cout << endl;
    }
}

void findItems(int B[101][101], int weights[101], int n, int W) {
    int i = n;
    int k = W;
    int selected[101] = {0};

    cout << "\nSelected items: ";

    while (i > 0 && k > 0) {
        if (B[i][k] != B[i - 1][k]) {
            cout << i << " ";
            selected[i] = 1;
            k = k - weights[i];
        }
        i--;
    }

    cout << endl;

    cout << "Item inclusion: ";
    for (int j = 1; j <= n; j++) {
        cout << selected[j] << " ";
    }
    cout << endl;
}

void Knapsack_ALgo(int profits[101], int weights[101], int n, int W) {
    int B[101][101];

    for (int r = 0; r <= n; r++) { //col 0 all values are 0
        B[r][0] = 0;
    }

    for (int c = 0; c <= W; c++) { //row 0 all values are 0
        B[0][c] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int c = 1; c <= W; c++) {
            if (weights[i] <= c) {
                if (profits[i] + B[i - 1][c - weights[i]] > B[i - 1][c]) {
                    B[i][c] = profits[i] + B[i - 1][c - weights[i]];
                } else {
                    B[i][c] = B[i - 1][c];
                }
            } else {
                B[i][c] = B[i - 1][c];
            }
        }
    }

    Display(B, n, W);
    cout << "\nMaximum profits: " << B[n][W] << endl;

    findItems(B, weights, n, W);
}

int main() {
    int choice;
    int n, W;
    int profits[101], weights[101];
    Knapsack items[101];

    while (true) {
        cout << "\n\t0-1 Knapsack menu" << endl;
        cout << "1. Solve knapsack" << endl;
        cout << "2. Exit" << endl;
        cout << "enter choice: ";
        cin >> choice;

        if (choice == 2) {
            cout << "exiting..." << endl;
            break;
        } else if (choice == 1) {
            cout << "enter number of objects: ";
            cin >> n;
            cout << "enter knapsack capacity: ";
            cin >> W;

            for (int i = 1; i <= n; i++) {
                cout << "enter weight and profit for item " << i << ": ";
                cin >> items[i].w >> items[i].p;
                weights[i] = items[i].w;
                profits[i] = items[i].p;
            }

            Knapsack_ALgo(profits, weights, n, W);
        } else {
            cout << "Invalid choice! try again." << endl;
        }
    }

    return 0;
}
