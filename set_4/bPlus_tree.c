#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 3   // order of B+ tree (max children per node)

typedef struct BPTreeNode {
    int keys[M];
    struct BPTreeNode* child[M+1];
    struct BPTreeNode* next; // for leaf chaining
    bool isLeaf;
    int n; // number of keys
} BPTreeNode;

BPTreeNode* createNode(bool isLeaf) {
    BPTreeNode* node = (BPTreeNode*)malloc(sizeof(BPTreeNode));
    node->isLeaf = isLeaf;
    node->n = 0;
    node->next = NULL;
    for (int i=0;i<=M;i++) node->child[i]=NULL;
    return node;
}

void traverse(BPTreeNode* root) {
    if (!root) return;
    if (root->isLeaf) {
        for (int i=0;i<root->n;i++) printf("%d ", root->keys[i]);
    } else {
        for (int i=0;i<root->n;i++) {
            traverse(root->child[i]);
            printf("%d ", root->keys[i]);
        }
        traverse(root->child[root->n]);
    }
}

BPTreeNode* searchItem(BPTreeNode* root,int key){
    if(!root) return NULL;
    int i=0;
    while(i<root->n && key>root->keys[i]) i++;
    if(root->isLeaf){
        if(i<root->n && root->keys[i]==key) return root;
        return NULL;
    }
    return searchItem(root->child[i],key);
}

void splitChild(BPTreeNode* parent,int i){
    BPTreeNode* y=parent->child[i];
    int mid=y->n/2;

    BPTreeNode* z=createNode(y->isLeaf);
    z->n=y->n-mid;
    for(int j=0;j<z->n;j++) z->keys[j]=y->keys[mid+j];
    if(!y->isLeaf) for(int j=0;j<=z->n;j++) z->child[j]=y->child[mid+j];
    y->n=mid;

    for(int j=parent->n;j>=i+1;j--) parent->child[j+1]=parent->child[j];
    parent->child[i+1]=z;
    for(int j=parent->n-1;j>=i;j--) parent->keys[j+1]=parent->keys[j];
    parent->keys[i]=z->keys[0];
    parent->n++;
    
    if(y->isLeaf){ 
        z->next=y->next; y->next=z;
    }
}

void insertNonFull(BPTreeNode* node,int key){
    int i=node->n-1;
    if(node->isLeaf){
        while(i>=0 && key<node->keys[i]){
            node->keys[i+1]=node->keys[i]; i--;
        }
        node->keys[i+1]=key;
        node->n++;
    } else {
        while(i>=0 && key<node->keys[i]) i--;
        i++;
        if(node->child[i]->n==M){
            splitChild(node,i);
            if(key>node->keys[i]) i++;
        }
        insertNonFull(node->child[i],key);
    }
}

BPTreeNode* insertItem(BPTreeNode* root,int key){
    if(!root){
        root=createNode(true);
        root->keys[0]=key; root->n=1;
        return root;
    }
    if(root->n==M){
        BPTreeNode* s=createNode(false);
        s->child[0]=root;
        splitChild(s,0);
        int i=0;
        if(key>s->keys[0]) i++;
        insertNonFull(s->child[i],key);
        return s;
    }
    insertNonFull(root,key);
    return root;
}

// (simple leaf-only deletion, no merge for brevity)
BPTreeNode* deleteItem(BPTreeNode* root,int key){
    if(!root) return NULL;
    if(root->isLeaf){
        int i,j;
        for(i=0;i<root->n && root->keys[i]!=key;i++);
        if(i==root->n) return root;
        for(j=i;j<root->n-1;j++) root->keys[j]=root->keys[j+1];
        root->n--;
        if(root->n==0) { free(root); return NULL; }
        return root;
    }
    int i=0; while(i<root->n && key>root->keys[i]) i++;
    root->child[i]=deleteItem(root->child[i],key);
    return root;
}

// Demo
int main(){
    BPTreeNode* root=NULL;
    root=insertItem(root,10);
    root=insertItem(root,20);
    root=insertItem(root,5);
    root=insertItem(root,6);
    root=insertItem(root,12);
    root=insertItem(root,30);
    root=insertItem(root,7);
    root=insertItem(root,17);

    printf("Traversal: "); traverse(root); printf("\n");

    root=deleteItem(root,6);
    printf("After deletion of 6: "); traverse(root); printf("\n");

    BPTreeNode* s=searchItem(root,12);
    printf("Search 12: %s\n", s?"Found":"Not Found");
}