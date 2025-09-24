#include <stdio.h>
#include <stdlib.h>

#define T 3   // Minimum degree (order). Each node can have [T-1 .. 2*T-1] keys.

typedef struct BTreeNode {
    int keys[2*T-1], n;
    struct BTreeNode *child[2*T];
    int leaf;
} BTreeNode;

BTreeNode* createItem(int leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->n = 0;
    node->leaf = leaf;
    for (int i=0; i<2*T; i++) node->child[i] = NULL;
    return node;
}

BTreeNode* searchItem(BTreeNode* root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i]) i++;
    if (i < root->n && root->keys[i] == k) return root;
    if (root->leaf) return NULL;
    return searchItem(root->child[i], k);
}

void splitChild(BTreeNode* x, int i) {
    BTreeNode* y = x->child[i];
    BTreeNode* z = createItem(y->leaf);
    z->n = T-1;

    for (int j=0;j<T-1;j++) z->keys[j] = y->keys[j+T];
    if (!y->leaf)
        for (int j=0;j<T;j++) z->child[j] = y->child[j+T];

    y->n = T-1;
    for (int j=x->n; j>=i+1; j--) x->child[j+1] = x->child[j];
    x->child[i+1] = z;
    for (int j=x->n-1; j>=i; j--) x->keys[j+1] = x->keys[j];
    x->keys[i] = y->keys[T-1];
    x->n++;
}

void insertNonFull(BTreeNode* x, int k) {
    int i = x->n-1;
    if (x->leaf) {
        while (i>=0 && k<x->keys[i]) { x->keys[i+1] = x->keys[i]; i--; }
        x->keys[i+1] = k;
        x->n++;
    } else {
        while (i>=0 && k<x->keys[i]) i--;
        i++;
        if (x->child[i]->n == 2*T-1) {
            splitChild(x,i);
            if (k > x->keys[i]) i++;
        }
        insertNonFull(x->child[i],k);
    }
}

BTreeNode* insertItem(BTreeNode* root, int k) {
    if (root->n == 2*T-1) {
        BTreeNode* s = createItem(0);
        s->child[0] = root;
        splitChild(s,0);
        int i = (k > s->keys[0]);
        insertNonFull(s->child[i],k);
        return s;
    } else {
        insertNonFull(root,k);
        return root;
    }
}

int getPred(BTreeNode* x) {
    BTreeNode* cur = x;
    while (!cur->leaf) cur = cur->child[cur->n];
    return cur->keys[cur->n-1];
}
int getSucc(BTreeNode* x) {
    BTreeNode* cur = x;
    while (!cur->leaf) cur = cur->child[0];
    return cur->keys[0];
}

void merge(BTreeNode* x,int idx) {
    BTreeNode* c1 = x->child[idx];
    BTreeNode* c2 = x->child[idx+1];
    c1->keys[T-1] = x->keys[idx];
    for (int i=0;i<c2->n;i++) c1->keys[i+T] = c2->keys[i];
    if (!c1->leaf) for (int i=0;i<=c2->n;i++) c1->child[i+T] = c2->child[i];
    for (int i=idx+1;i<x->n;i++) x->keys[i-1] = x->keys[i];
    for (int i=idx+2;i<=x->n;i++) x->child[i-1] = x->child[i];
    c1->n += c2->n+1; x->n--;
    free(c2);
}

void fill(BTreeNode* x,int idx);

void borrowFromPrev(BTreeNode* x,int idx) {
    BTreeNode* c = x->child[idx];
    BTreeNode* sib = x->child[idx-1];
    for (int i=c->n-1;i>=0;i--) c->keys[i+1] = c->keys[i];
    if (!c->leaf) for (int i=c->n;i>=0;i--) c->child[i+1] = c->child[i];
    c->keys[0] = x->keys[idx-1];
    if (!c->leaf) c->child[0] = sib->child[sib->n];
    x->keys[idx-1] = sib->keys[sib->n-1];
    c->n++; sib->n--;
}

void borrowFromNext(BTreeNode* x,int idx) {
    BTreeNode* c = x->child[idx];
    BTreeNode* sib = x->child[idx+1];
    c->keys[c->n] = x->keys[idx];
    if (!c->leaf) c->child[c->n+1] = sib->child[0];
    x->keys[idx] = sib->keys[0];
    for (int i=1;i<sib->n;i++) sib->keys[i-1] = sib->keys[i];
    if (!sib->leaf) for (int i=1;i<=sib->n;i++) sib->child[i-1] = sib->child[i];
    c->n++; sib->n--;
}

void fill(BTreeNode* x,int idx) {
    if (idx!=0 && x->child[idx-1]->n>=T) borrowFromPrev(x,idx);
    else if (idx!=x->n && x->child[idx+1]->n>=T) borrowFromNext(x,idx);
    else {
        if (idx!=x->n) merge(x,idx);
        else merge(x,idx-1);
    }
}

void deleteNode(BTreeNode* x,int k);

void deleteFromLeaf(BTreeNode* x,int idx) {
    for (int i=idx+1;i<x->n;i++) x->keys[i-1] = x->keys[i];
    x->n--;
}

void deleteFromNonLeaf(BTreeNode* x,int idx) {
    int k = x->keys[idx];
    if (x->child[idx]->n >= T) {
        int pred = getPred(x->child[idx]);
        x->keys[idx] = pred;
        deleteNode(x->child[idx], pred);
    } else if (x->child[idx+1]->n >= T) {
        int succ = getSucc(x->child[idx+1]);
        x->keys[idx] = succ;
        deleteNode(x->child[idx+1], succ);
    } else {
        merge(x,idx);
        deleteNode(x->child[idx], k);
    }
}

void deleteNode(BTreeNode* x,int k) {
    int idx=0;
    while (idx<x->n && x->keys[idx]<k) idx++;
    if (idx<x->n && x->keys[idx]==k) {
        if (x->leaf) deleteFromLeaf(x,idx);
        else deleteFromNonLeaf(x,idx);
    } else {
        if (x->leaf) return;
        int flag = (idx==x->n);
        if (x->child[idx]->n<T) fill(x,idx);
        if (flag && idx>x->n) deleteNode(x->child[idx-1],k);
        else deleteNode(x->child[idx],k);
    }
}

BTreeNode* deleteItem(BTreeNode* root,int k) {
    if (!root) return NULL;
    deleteNode(root,k);
    if (root->n==0) {
        BTreeNode* tmp=root;
        root = root->leaf? NULL : root->child[0];
        free(tmp);
    }
    return root;
}

void inorder(BTreeNode* root) {
    if (!root) return;
    int i;
    for (i=0;i<root->n;i++) {
        inorder(root->child[i]);
        printf("%d ", root->keys[i]);
    }
    inorder(root->child[i]);
}

// Example usage
int main() {
    BTreeNode* root = createItem(1);

    root = insertItem(root,10);
    root = insertItem(root,20);
    root = insertItem(root,5);
    root = insertItem(root,6);
    root = insertItem(root,12);
    root = insertItem(root,30);
    root = insertItem(root,7);
    root = insertItem(root,17);

    printf("Traversal: ");
    inorder(root); printf("\n");

    root = deleteItem(root,6);
    printf("After deleting 6: ");
    inorder(root); printf("\n");

    root = deleteItem(root,13);
    printf("After deleting 13: ");
    inorder(root); printf("\n");

    BTreeNode* found = searchItem(root, 12);
    printf("Search 12: %s\n", found ? "Found" : "Not Found");

    return 0;
}