#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key, height;
    struct Node *left, *right;
} Node;

// Utility functions
int h(Node *n) {
    return n ? n->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create new node
Node* createItem(int key) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

// Right rotation
Node* rotR(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;

    y->height = 1 + max(h(y->left), h(y->right));
    x->height = 1 + max(h(x->left), h(x->right));

    return x;
}

// Left rotation
Node* rotL(Node* x) {
    Node* y = x->right;
    Node* T = y->left;

    y->left = x;
    x->right = T;

    x->height = 1 + max(h(x->left), h(x->right));
    y->height = 1 + max(h(y->left), h(y->right));

    return y;
}

// Balance factor
int bal(Node* n) {
    return n ? h(n->left) - h(n->right) : 0;
}

// Insert
Node* insertItem(Node* root, int key) {
    if (!root) return createItem(key);

    if (key < root->key)
        root->left = insertItem(root->left, key);
    else if (key > root->key)
        root->right = insertItem(root->right, key);
    else
        return root;

    root->height = 1 + max(h(root->left), h(root->right));
    int b = bal(root);

    if (b > 1 && key < root->left->key) return rotR(root);
    if (b < -1 && key > root->right->key) return rotL(root);
    if (b > 1 && key > root->left->key) {
        root->left = rotL(root->left);
        return rotR(root);
    }
    if (b < -1 && key < root->right->key) {
        root->right = rotR(root->right);
        return rotL(root);
    }
    return root;
}

// Minimum value node
Node* minVal(Node* n) {
    return n->left ? minVal(n->left) : n;
}

// Delete
Node* deleteItem(Node* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteItem(root->left, key);
    else if (key > root->key)
        root->right = deleteItem(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* tmp = root->left ? root->left : root->right;
            if (!tmp) {
                tmp = root;
                root = NULL;
            } else {
                *root = *tmp;
            }
            free(tmp);
        } else {
            Node* tmp = minVal(root->right);
            root->key = tmp->key;
            root->right = deleteItem(root->right, tmp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + max(h(root->left), h(root->right));
    int b = bal(root);

    if (b > 1 && bal(root->left) >= 0) return rotR(root);
    if (b > 1 && bal(root->left) < 0) {
        root->left = rotL(root->left);
        return rotR(root);
    }
    if (b < -1 && bal(root->right) <= 0) return rotL(root);
    if (b < -1 && bal(root->right) > 0) {
        root->right = rotR(root->right);
        return rotL(root);
    }
    return root;
}

// Search
Node* searchItem(Node* root, int key) {
    if (!root || root->key == key) return root;
    return (key < root->key) ? searchItem(root->left, key) : searchItem(root->right, key);
}

// Inorder traversal for testing
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

// Example usage
int main() {
    Node* root = NULL;

    root = insertItem(root, 10);
    root = insertItem(root, 20);
    root = insertItem(root, 30);
    root = insertItem(root, 40);
    root = insertItem(root, 50);
    root = insertItem(root, 25);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    root = deleteItem(root, 30);
    printf("After deleting 30: ");
    inorder(root);
    printf("\n");

    Node* found = searchItem(root, 25);
    printf("Search 25: %s\n", found ? "Found" : "Not Found");

    return 0;
}