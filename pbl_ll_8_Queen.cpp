//Write a program for Hamiltonian Problem OR N-Queen problem using Backtracking approach.

#include <iostream>
#include <cmath>
using namespace std;

int x[20];

void display(int n);

bool place(int k, int i) {
    for (int j = 1; j < k; j++) {
        if (x[j] == i || abs(x[j] - i) == abs(j - k)) {
            return false;
        }
    }
    return true;
}

void NQueen(int k, int n) {
    for (int i = 1; i <= n; i++) {
        if (place(k, i)) {
            x[k] = i;
            if (k == n) {
                display(n);
                for (int j = 1; j <= n; j++) {
                    cout << "x" << j << "=" << x[j];
                    if (j < n)
                        cout << ",";
                }
                cout << endl;
            } else {
                NQueen(k + 1, n);
            }
            x[k] = 0;
        }
    }
}


void display(int n) {
    cout << "Chessboard: \n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i] == j)
                cout << "Q ";
            else
                cout << "_ ";
        }
        cout << endl;
    }
    cout << endl;
}


int main() {
    int n;
    cout << "Enter the size of chessboard: ";
    cin >> n;
    NQueen(1, n);
    return 0;
}

