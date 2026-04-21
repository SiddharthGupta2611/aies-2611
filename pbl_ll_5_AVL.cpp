/*
    Write a program to implement AVL tree for Dictionary. A Dictionary stores keywords & its meaning.
    Provide facility for adding new keywords, updating meaning of any entry. 
    Provide a facility to display whole data sorted in ascending order. 
    Also find how many maximum comparisons may require for finding any keyword. 
    Use a Height balanced tree and find the complexity for finding a keyword.
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class avl_node {
    string word, meaning;
    avl_node *left, *right;
public:
    friend class avlTree;
    avl_node() : left(NULL), right(NULL) {}
};

class avlTree {
    avl_node *root;
public:
    int height(avl_node*);
    int diff(avl_node*);
    avl_node* rr_rotation(avl_node*);
    avl_node* ll_rotation(avl_node*);
    avl_node* lr_rotation(avl_node*);
    avl_node* rl_rotation(avl_node*);
    avl_node* balance(avl_node*);
    void insert();
    avl_node* insert(avl_node*, avl_node*);
    void display(avl_node*, int);
    void inorder(avl_node*);
    void preorder(avl_node*);
    void postorder(avl_node*);
    avl_node* getRoot() { return root; }
   
    avlTree() { root = NULL; }
};

int avlTree :: height(avl_node* temp) {
    if (temp == NULL) return 0;
    int l_height = height(temp->left);
    int r_height = height(temp->right);
    return max(l_height, r_height) + 1;
}

int avlTree :: diff(avl_node* temp) {
    if (temp == NULL) return 0;
    return height(temp->left) - height(temp->right);
}

avl_node* avlTree :: ll_rotation(avl_node* parent) {
    avl_node* temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

avl_node* avlTree :: rr_rotation(avl_node* parent) {
    avl_node* temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

avl_node* avlTree :: lr_rotation(avl_node* parent) {
    avl_node* temp = parent->left;
    parent->left = rr_rotation(temp);
    return ll_rotation(parent);
}

avl_node* avlTree :: rl_rotation(avl_node* parent) {
    avl_node* temp = parent->right;
    parent->right = ll_rotation(temp);
    return rr_rotation(parent);
}

avl_node* avlTree :: balance(avl_node* temp) {
    int bal_factor = diff(temp);
    if (bal_factor > 1) {
        if (diff(temp->left) > 0)
            temp = ll_rotation(temp);
        else
            temp = lr_rotation(temp);
    }
    else if (bal_factor < -1) {
        if (diff(temp->right) < 0)
            temp = rr_rotation(temp);
        else
            temp = rl_rotation(temp);
    }
    return temp;
}

void avlTree :: insert() {
    char ch;
    do {
        avl_node* temp = new avl_node;
        cout << "Enter word and its meaning: ";
        cin >> temp->word >> temp->meaning;
        root = insert(root, temp);
        cout << "Continue? (Y/N): ";
        cin >> ch;
    } while (toupper(ch) == 'Y');
}

avl_node* avlTree :: insert(avl_node* root_node, avl_node* temp) {
    if (root_node == NULL) {
        root_node = temp;
        return root_node;
    }
    else if (temp->word < root_node->word) {
        root_node->left = insert(root_node->left, temp);
        root_node = balance(root_node);
    }
    else if (temp->word > root_node->word) {
        root_node->right = insert(root_node->right, temp);
        root_node = balance(root_node);
    }
    return root_node;
}

void avlTree :: display(avl_node* node, int level) {
    if (node != NULL) {
        display(node->right, level + 1);
        for (int i = 0; i < level; i++) cout << "    ";
        cout << node->word << " (" << node->meaning << ")" << endl;
        display(node->left, level + 1);
    }
}

void avlTree :: inorder(avl_node* node) {
    if (node != NULL) {
        inorder(node->left);
        cout << node->word << " : " << node->meaning << endl;
        inorder(node->right);
    }
}

void avlTree :: preorder(avl_node* node) {
    if (node != NULL) {
        cout << node->word << " : " << node->meaning << endl;
        preorder(node->left);
        preorder(node->right);
    }
}

void avlTree :: postorder(avl_node* node) {
    if (node != NULL) {
        postorder(node->left);
        postorder(node->right);
        cout << node->word << " : " << node->meaning << endl;
    }
}

int main() {
    avlTree tree;
    int choice;
   
    do {
        cout << "\n=== AVL Dictionary ===\n";
        cout << "1. Insert words\n";
        cout << "2. Inorder\n";
        cout << "3. Preorder\n";
        cout << "4. Postorder\n";
        cout << "5. Display tree\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
       
        switch (choice) {
            case 1: tree.insert(); break;
            case 2:
                cout << "\nInorder:\n";
                tree.inorder(tree.getRoot()); break;
            case 3:
                cout << "\nPreorder:\n";
                tree.preorder(tree.getRoot()); break;
            case 4:
                cout << "\nPostorder:\n";
                tree.postorder(tree.getRoot()); break;
            case 5:
                cout << "\nTree:\n";
                tree.display(tree.getRoot(), 0); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid!\n";
        }
    } while (choice != 0);
   
    return 0;
}