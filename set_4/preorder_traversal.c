// Implement preorder traversal algorithm for binary tree without using recursion.

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

// Utility function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Stack structure
struct Stack {
    struct Node* data[100]; // max size = 100 (can be made dynamic)
    int top;
};

void initStack(struct Stack* s) {
    s->top = -1;
}

int isEmpty(struct Stack* s) {
    return (s->top == -1);
}

void push(struct Stack* s, struct Node* node) {
    s->data[++(s->top)] = node;
}

struct Node* pop(struct Stack* s) {
    return s->data[(s->top)--];
}

// Iterative Preorder Traversal
void preorder(struct Node* root) {
    if (root == NULL) return;

    struct Stack stack;
    initStack(&stack);

    push(&stack, root);

    while (!isEmpty(&stack)) {
        struct Node* curr = pop(&stack);
        printf("%d ", curr->data);

        // Push right first, so left is processed first
        if (curr->right) push(&stack, curr->right);
        if (curr->left) push(&stack, curr->left);
    }
}

int main() {
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    printf("Preorder Traversal (Iterative): ");
    preorder(root);
    printf("\n");

    return 0;
}
