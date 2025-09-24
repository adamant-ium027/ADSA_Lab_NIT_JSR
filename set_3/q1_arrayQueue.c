// Implement a circular queue using an array

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 100

int arr[N];
int front = -1, rear = -1;

void enqueue(int);
void dequeue();
int peek_front();
int peek_rear();
bool is_empty();
bool is_full();

int main(void){
    enqueue(10);
    enqueue(20);
    enqueue(30);
    dequeue();

    printf("front = %d, rear = %d, is_empty = %d, is_full = %d\n", peek_front(), peek_rear(), is_empty(), is_full());

    return 0;
}

void enqueue(int data){
    if(is_full()) return;

    if(front == -1 && rear == -1){
        front = rear = 0;
        arr[rear] = data;
    }
    else if(rear < N-1){
        arr[++rear] = data;
    }
    else if(rear == N-1){
        if(front == 0){
            return;
        }
        else if(front > 0){
            rear = 0;
            arr[rear] = data;
        }
    }
}

void dequeue(){
    if(is_empty()) return;

    if(front == rear){
        front = rear = -1;
    }
    else if(front < rear){
        front++;
    }
    else if(front > rear){
        if(front < N-1) front++;
        else if(front == N-1){
            front = 0;
        }
    }
}

int peek_rear(){
    if(is_empty()){
        printf("Queue is empty\n");
        return -1;
    }

    return arr[rear];
}

int peek_front(){
    if(is_empty()){
        printf("Queue is empty\n");
        return -1;
    }
    
    return arr[front];
}

bool is_empty(){
    if(front == -1) return true;
    
    return false;
}

bool is_full(){
    if((front == rear + 1) || (front == 0 && rear == N-1)) return true;

    return false;
}