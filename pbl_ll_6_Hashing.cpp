#include <iostream>
#include <string>
using namespace std;

#define MAX 10

class record {
    int rNo, marks;
    char name[50];
    friend class student;
};

class hashing {
    int rNo, pos;
public:
    hashing() {
        rNo = -1;
        pos = -1;
    }
    friend class student;
};

class student {
    record rec;
    hashing h[MAX];
    record table[MAX];   // store student records in hash table

public:
    student();
    void insert_withoutReplacement(); // linear probing only
    void insert_withReplacement();    // replacement + reinsert displaced record
    void modify();
    void delete_rec();
    void display();
    void search(int rNo);
};

// constructor
student::student() {
    for (int i = 0; i < MAX; i++) {
        h[i].rNo = -1;
        h[i].pos = -1;
        table[i].rNo = -1;
        table[i].marks = -1;
        table[i].name[0] = '\0';
    }
}

// ✅ Insert WITHOUT replacement
// If slot is occupied, just probe forward until empty slot.
void student::insert_withoutReplacement() {
    cout << "Enter Roll No: ";
    cin >> rec.rNo;
    cout << "Enter Name: ";
    cin >> rec.name;
    cout << "Enter Marks: ";
    cin >> rec.marks;

    int loc = rec.rNo % MAX;
    if (table[loc].rNo == -1) {
        table[loc] = rec;
        h[loc].rNo = rec.rNo;
        h[loc].pos = loc;
        return;
    } else {
        int i = (loc + 1) % MAX;
        while (i != loc) {
            if (table[i].rNo == -1) {
                table[i] = rec;
                h[i].rNo = rec.rNo;
                h[i].pos = i;
                return;
            }
            i = (i + 1) % MAX;
        }
        cout << "Hash table is full\n";
    }
}

// ✅ Insert WITH replacement
// If slot is occupied by a displaced record, replace it and reinsert displaced one.
void student::insert_withReplacement() {
    cout << "Enter Roll No: ";
    cin >> rec.rNo;
    cout << "Enter Name: ";
    cin >> rec.name;
    cout << "Enter Marks: ";
    cin >> rec.marks;

    int loc = rec.rNo % MAX;
    if (table[loc].rNo == -1) {
        table[loc] = rec;
        h[loc].rNo = rec.rNo;
        h[loc].pos = loc;
        return;
    } else {
        record temp = rec;
        // If the existing record is not in its home slot, replace it
        if (loc != (table[loc].rNo % MAX)) {
            temp = table[loc];
            table[loc] = rec;
        }
        int i = (loc + 1) % MAX;
        while (i != loc) {
            if (table[i].rNo == -1) {
                table[i] = temp;
                h[i].rNo = temp.rNo;
                h[i].pos = i;
                return;
            }
            i = (i + 1) % MAX;
        }
        cout << "Hash table is full\n";
    }
}

void student::search(int rNo) {
    int loc = rNo % MAX;
    int i = loc;
    do {
        if (table[i].rNo == rNo) {
            cout << "Found at position " << i << ": "
                 << "Roll No: " << table[i].rNo
                 << ", Name: " << table[i].name
                 << ", Marks: " << table[i].marks << endl;
            return;
        }
        i = (i + 1) % MAX;
    } while (i != loc);
    cout << "Record not found\n";
}

void student::delete_rec() {
    int rNo;
    cout << "Enter Roll No to delete: ";
    cin >> rNo;

    int loc = rNo % MAX;
    int i = loc;
    do {
        if (table[i].rNo == rNo) {
            table[i].rNo = -1;
            table[i].marks = -1;
            table[i].name[0] = '\0';
            h[i].rNo = -1;
            h[i].pos = -1;
            cout << "Record deleted from position " << i << endl;
            return;
        }
        i = (i + 1) % MAX;
    } while (i != loc);
    cout << "Record not found\n";
}

void student::modify() {
    int rNo;
    cout << "Enter Roll No to modify: ";
    cin >> rNo;

    int loc = rNo % MAX;
    int i = loc;
    do {
        if (table[i].rNo == rNo) {
            cout << "Enter new Name: ";
            cin >> table[i].name;
            cout << "Enter new Marks: ";
            cin >> table[i].marks;
            cout << "Record modified at position " << i << endl;
            return;
        }
        i = (i + 1) % MAX;
    } while (i != loc);
    cout << "Record not found\n";
}

void student::display() {
    cout << "\nHash Table:\n";
    for (int i = 0; i < MAX; i++) {
        if (table[i].rNo != -1) {
            cout << i << " --> Roll No: " << table[i].rNo
                 << ", Name: " << table[i].name
                 << ", Marks: " << table[i].marks << endl;
        } else {
            cout << i << " --> Empty\n";
        }
    }
}

int main() {
    student s;
    int choice, rNo;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert WITHOUT replacement\n";
        cout << "2. Insert WITH replacement\n";
        cout << "3. Search\n";
        cout << "4. Delete\n";
        cout << "5. Modify\n";
        cout << "6. Display\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: s.insert_withoutReplacement();
                break;
        case 2: s.insert_withReplacement();
                break;
        case 3: cout << "Enter Roll No to search: ";
                cin >> rNo;
                s.search(rNo);
                break;
        case 4: s.delete_rec();
                break;
        case 5: s.modify();
                break;
        case 6: s.display();
                break;
        case 7: return 0;
        default: cout << "Invalid choice\n";
        }
    }
}
