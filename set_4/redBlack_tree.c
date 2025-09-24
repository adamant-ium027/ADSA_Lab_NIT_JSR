#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int key;
    Color color;
    struct Node *left, *right, *parent;
} Node;

Node* NIL;  // Sentinel node for leaves

// Create a new node
Node* createItem(int key) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->color = RED;
    n->left = n->right = n->parent = NIL;
    return n;
}

// Left rotate
void rotL(Node** root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Right rotate
void rotR(Node** root, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NIL) x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NIL) *root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// Fix violation after insert
void insertFix(Node** root, Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotL(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotR(root, z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotR(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotL(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

// Insert a node
void insertItem(Node** root, int key) {
    Node* z = createItem(key);
    Node* y = NIL;
    Node* x = *root;

    while (x != NIL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (y == NIL) *root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;

    z->left = z->right = NIL;
    z->color = RED;
    insertFix(root, z);
}

// Search
Node* searchItem(Node* root, int key) {
    if (root == NIL || root->key == key) return root;
    return (key < root->key) ? searchItem(root->left, key) : searchItem(root->right, key);
}

// Find minimum
Node* minVal(Node* n) {
    while (n->left != NIL) n = n->left;
    return n;
}

// Fix violation after delete
void deleteFix(Node** root, Node* x) {
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotL(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotR(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotL(root, x->parent);
                x = *root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotR(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotL(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotR(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

// Transplant
void transplant(Node** root, Node* u, Node* v) {
    if (u->parent == NIL) *root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

// Delete
void deleteItem(Node** root, int key) {
    Node* z = searchItem(*root, key);
    if (z == NIL) return;

    Node* y = z;
    Node* x;
    Color yColor = y->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = minVal(z->right);
        yColor = y->color;
        x = y->right;
        if (y->parent == z) x->parent = y;
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yColor == BLACK) deleteFix(root, x);
    free(z);
}

// Inorder traversal
void inorder(Node* root) {
    if (root == NIL) return;
    inorder(root->left);
    printf("%d(%s) ", root->key, root->color == RED ? "R" : "B");
    inorder(root->right);
}

// Example usage
int main() {
    // Initialize NIL sentinel
    NIL = (Node*)malloc(sizeof(Node));
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NIL;

    Node* root = NIL;

    insertItem(&root, 10);
    insertItem(&root, 20);
    insertItem(&root, 30);
    insertItem(&root, 15);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    deleteItem(&root, 20);
    printf("After deleting 20: ");
    inorder(root);
    printf("\n");

    Node* found = searchItem(root, 15);
    printf("Search 15: %s\n", found != NIL ? "Found" : "Not Found");

    return 0;
}