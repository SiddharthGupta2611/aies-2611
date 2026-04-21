/*
	Write a program for Iterative and Recursive Binary Search and verify the time complexity.
    Accept Mobile user information (e.g. MobileNo, Name, BillAmount etc.).
    Display details for Mobileno specified by user (Linear Search and Recursive and Non-recursive Binary Search)
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class MobileUser {
    long int mobile_no;
    string name;
    long int billamount;
   
public:
    MobileUser() {
        mobile_no = 0;
        name = "-";
        billamount = 0;
    }
    friend class Records;
   
    long int getMobileNo() const { return mobile_no; }
    string getName() const { return name; }
};

class Records {
    MobileUser M[10];
    int n;
   
public:
    Records(int n1) {
        n = n1;
    }
    void accept();  
    void display();
    int linear_Search(long int key);
    int Binary_Search(string key_name);
};

void Records :: accept() {
    for(int i = 0; i < n; i++) {
        cout << "\nEnter details for user " << (i+1) << ":" << endl;
        cout << "Mobile Number: ";
        cin >> M[i].mobile_no;
        cout << "Name: ";
        cin.ignore(); // Clear buffer before reading name
        getline(cin, M[i].name);
        cout << "Bill Amount: ";
        cin >> M[i].billamount;
    }
}

void Records :: display() {
    cout << "\n" << string(60, '=') << endl;
    cout << "Mobile No.\t\tName\t\t\tBill Amount" << endl;
    cout << string(60, '=') << endl;
    for(int i = 0; i < n; i++) {
        cout << M[i].mobile_no << "\t\t" << M[i].name << "\t\t\t" << M[i].billamount << endl;
    }
    cout << string(60, '=') << endl;
}

int Records :: linear_Search(long int key) {
    for(int i = 0; i < n; i++) {
        if(M[i].getMobileNo() == key) {
            return i + 1;
        }
    }
    return -1;
}

int Records :: Binary_Search(string key_name) {
    // Create indices array
    int indices[10];
    for(int i = 0; i < n; i++) {
        indices[i] = i;
    }
   
    // Sort indices based on names using bubble sort
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(M[indices[j]].getName() > M[indices[j+1]].getName()) {
                swap(indices[j], indices[j+1]);
            }
        }
    }
   
    // Binary search on sorted indices
    int l = 0, h = n - 1;
    while(l <= h) {
        int mid = (l + h) / 2;
        int mid_idx = indices[mid];
       
        if(M[mid_idx].getName() == key_name) {
            return mid_idx + 1;
        }
        else if(key_name < M[mid_idx].getName()) {
            h = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    return -1;
}

int main() {
    int n, choice;
    long int key;
    string name_key;
    int index;
   
    cout << " Mobile User Records System" << endl;
    cout << "Enter number of records (max 10): ";
    cin >> n;
   
    if(n <= 0 || n > 10) {
        cout << "Invalid number! Must be between 1 and 10." << endl;
        return 1;
    }
   
    Records r(n);
   
    while(true) {
        cout << "\n=== MENU ===" << endl;
        cout << "1. Accept data" << endl;
        cout << "2. Display data" << endl;    
        cout << "3. Search by Mobile Number (Linear Search)" << endl;
        cout << "4. Search by Name (Binary Search)" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
       
        switch(choice) {
            case 1: r.accept();
                    break;
               
            case 2: r.display();
                    break;
               
            case 3: cout << "\n     Linear Search" << endl;
                    cout << "Enter Mobile Number: ";
                    cin >> key;
                    index = r.linear_Search(key);
                    if(index != -1)
                        cout << " Mobile " << key << " found at position " << index << endl;
                    else
                        cout << " Mobile " << key << " not found" << endl;
                    break;
               
            case 4: cout << "\n     Binary Search" << endl;
                    cout << "Enter Name: ";
                    cin.ignore();
                    getline(cin, name_key);
                    index = r.Binary_Search(name_key);
                    if(index != -1)
                        cout << " Name '" << name_key << "' found at position " << index << endl;
                    else
                        cout << " Name '" << name_key << "' not found" << endl;
                    break;    
               
            case 5: cout << "\nThank you. Goodbye!" << endl;
                    return 0;
               
            default: cout << "INVALID CHOICE! Please select 1-5." << endl;
        }
    }
    return 0;
}