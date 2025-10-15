#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define N 4
#define SIZE (N*N)
#define MAX_NODES 1000000
#define HASH_SIZE 2000003  // prime for visited hash

// Goal state as 1D array
int goal[SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};

// Directions: up, down, left, right
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};
char moves[] = {'U','D','L','R'};

// Node in heap
typedef struct Node {
    uint64_t board;   // 64-bit packed board (4 bits per tile)
    int zx, zy;       // blank coordinates
    int level;        // g(n)
    int cost;         // f(n) = g + h
    struct Node* parent;
    char move;        // move that led here
} Node;

// Min-heap
Node* heap[MAX_NODES];
int heap_size = 0;

// Hash table for visited boards
uint64_t visited[HASH_SIZE];

// Swap heap nodes
void swap(int i,int j){ Node* t=heap[i]; heap[i]=heap[j]; heap[j]=t; }

// Heap operations
void heapify_up(int i){
    while(i>0 && heap[i]->cost<heap[(i-1)/2]->cost){
        swap(i,(i-1)/2);
        i=(i-1)/2;
    }
}
void heapify_down(int i){
    int smallest=i,l=2*i+1,r=2*i+2;
    if(l<heap_size && heap[l]->cost<heap[smallest]->cost) smallest=l;
    if(r<heap_size && heap[r]->cost<heap[smallest]->cost) smallest=r;
    if(smallest!=i){ swap(i,smallest); heapify_down(smallest);}
}
void push(Node* n){ heap[heap_size]=n; heapify_up(heap_size++);}
Node* pop(){ Node* t=heap[0]; heap[0]=heap[--heap_size]; heapify_down(0); return t; }

// Pack board into 64-bit integer
uint64_t pack_board(int mat[SIZE]){
    uint64_t b=0;
    for(int i=0;i<SIZE;i++){
        b <<= 4;
        b |= (mat[i] & 0xF);
    }
    return b;
}

// Unpack 64-bit board into array
void unpack_board(uint64_t b, int mat[SIZE]){
    for(int i=SIZE-1;i>=0;i--){
        mat[i] = b & 0xF;
        b >>=4;
    }
}

// Manhattan distance
int manhattan(uint64_t b){
    int mat[SIZE]; unpack_board(b, mat);
    int dist=0;
    for(int i=0;i<SIZE;i++){
        if(mat[i]==0) continue;
        int val=mat[i]-1;
        dist += abs(i/N - val/N) + abs(i%N - val%N);
    }
    return dist;
}

// Hash function for visited table
uint64_t hash_board(uint64_t b){
    return b % HASH_SIZE;
}

// Check goal
int is_goal(uint64_t b){
    int mat[SIZE]; unpack_board(b, mat);
    for(int i=0;i<SIZE;i++) if(mat[i]!=goal[i]) return 0;
    return 1;
}

// Print solution path
void print_path(Node* n){
    int len=0;
    Node* path[1000];
    while(n){ path[len++]=n; n=n->parent; }
    printf("Solution found in %d moves:\n", len-1);
    for(int i=len-1;i>=0;i--){
        int mat[SIZE]; unpack_board(path[i]->board, mat);
        for(int r=0;r<N;r++){
            for(int c=0;c<N;c++){
                if(mat[r*N+c]==0) printf("   ");
                else printf("%2d ", mat[r*N+c]);
            }
            printf("\n");
        }
        if(i>0) printf("Move: %c\n", path[i-1]->move);
        printf("\n");
    }
}

// Branch & Bound solver
void solve(int initial[SIZE]){
    Node* root = malloc(sizeof(Node));
    root->board = pack_board(initial);

    // find blank
    for(int i=0;i<SIZE;i++){
        if(initial[i]==0){ root->zx=i/N; root->zy=i%N; break; }
    }
    root->level=0;
    root->cost = manhattan(root->board);
    root->parent=NULL;
    root->move=0;

    memset(visited,0,sizeof(visited));
    visited[hash_board(root->board)]=1;

    heap_size=0; push(root);

    while(heap_size){
        Node* curr = pop();
        if(is_goal(curr->board)){
            print_path(curr);
            return;
        }

        int mat[SIZE]; unpack_board(curr->board, mat);
        for(int d=0;d<4;d++){
            int nx=curr->zx+dr[d], ny=curr->zy+dc[d];
            if(nx>=0 && nx<N && ny>=0 && ny<N){
                int idx1=curr->zx*N+curr->zy, idx2=nx*N+ny;
                int tmp = mat[idx1]; mat[idx1]=mat[idx2]; mat[idx2]=tmp;

                uint64_t packed = pack_board(mat);
                if(!visited[hash_board(packed)]){
                    visited[hash_board(packed)]=1;
                    Node* child = malloc(sizeof(Node));
                    child->board=packed;
                    child->zx=nx; child->zy=ny;
                    child->level=curr->level+1;
                    child->cost=child->level + manhattan(packed);
                    child->parent=curr;
                    child->move=moves[d];
                    push(child);
                }

                mat[idx2]=mat[idx1]; mat[idx1]=tmp; // undo
            }
        }
    }
    printf("No solution found.\n");
}

int main(){
    int initial[SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,15,14,0};
    printf("Initial state:\n");
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            int val = initial[i*N+j];
            if(val==0) printf("   ");
            else printf("%2d ", val);
        }
        printf("\n");
    }
    printf("\n");

    solve(initial);
    return 0;
}