/*
    Write a program to perform quick/merge sort using Divide and Conquer strategy and verify the time complexity.
        a.	Accept Mobile user information (e.g. MobileNo, Name, BillAmount etc.).
        b.	Display the data in descending order of MobileNo. (Recursive Quick Sort)
        c.	Display the data in ascending order of BillAmount (Heap Sort)
        d.	Display the number of passes and comparisons for different test cases (Worst, Average, Best case).
*/

#include <iostream>
#include <string>
using namespace std;

class MobileUser{
        long int mobilenum;
        string name;
        long int billamount;

    public:
        MobileUser(){
            mobilenum = 0;
            name = "-";
            billamount = 0;
        }
    friend class Records;
};

class Records{
        MobileUser M[10];
        int n;

public:
        Records(int n1){
            n = n1;
        }
        void accept();
        void display();
        void quickSort( int p, int r);
        int partition(int p, int r);
        void mergeSort(int l, int h);
        void merge(int l, int mid, int h);
        MobileUser temp[10];
};


void Records :: accept(){
    for(int i=0; i<n; i++){
        cout << "Enter the mobile number, name and bill amount: " << endl;
        cin >> M[i].mobilenum >> M[i].name >> M[i].billamount;
    }
}

void Records :: display(){
    cout << "Mobilenum" << "\t" << "Name "<< "\t "<< "Billamount "<< endl;
    for(int i=0; i<n; i++){
        cout << M[i].mobilenum << "\t\t"<< M[i].name << "\t " << M[i].billamount << endl;
    }
}


void Records :: mergeSort(int l, int h){
    if(l < h){
        int mid = (l+h)/2;
        mergeSort(l, mid);
        mergeSort(mid+1, h);
        merge(l, mid, h);
    }
}

void Records :: merge(int l, int mid, int h){
    int i = l;
    int j = mid+1;
    int k = l;
    while((i<=mid) && (j<=h)){
        if(M[i].mobilenum <= M[j].mobilenum){
            temp[k] = M[i];
            k++;
            i++;
        } else {
            temp[k] = M[j];
            k++;
            j++;
        }
    }
    
    while(i<=mid){
        temp[k] = M[i];
        k++;
        i++;
    }

    while(j<=h){
        temp[k] = M[j];
        k++;
        j++;
    }

    for(int k = l; k<=h; k++){
        M[k] = temp[k];
    }
}


void Records :: quickSort(int p, int r){
    if(p < r){
        int q = partition(p, r);
        quickSort(p, q-1);
        quickSort(q+1, r);
    }
}

int Records :: partition(int p, int r){
    MobileUser temp1;
    long int x = M[r].mobilenum;
    int i = p-1;
    for( int j = p ; j <= r-1; j++){
        if(M[j].mobilenum <= x){
            i++;
            temp1 = M[j];
            M[j] = M[i];
            M[i] = temp1;
        }
    }
        temp1 = M[r];
        M[r] = M[i+1];
        M[i+1] = temp1;
    return i+1;
}

int main(){
    int n;
    cout << "Enter your number of records: " << endl;
    cin >> n;

    Records R(n);
    R.accept();
    
    int c;
    int p = 0;
    int r = n - 1 ;
    
    while(true){
        cout << "\n1. Display\n2.Quick Sort\n3.Merge Sort\n4.Exit"<< endl;
        cin >> c;
        switch(c){
            case 1: R.display();
                    break;
            case 2: R.quickSort(p,r);
                    R.display();
                    break;
            case 3: R.mergeSort(p,r);
                    R.display();
                    break;
            case 4: cout << "Exiting...";
                    return 0;
            default: cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}

