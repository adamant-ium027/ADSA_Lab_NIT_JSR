#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define STACK_LEN 101

void push(char);
void pop();
char top();
bool is_empty();
bool is_full();
int size();

char arr[STACK_LEN];
int front = -1;

void push(char item){
    if(is_full()) return;

    arr[++front] = item;
}

void pop(){
    if(is_empty()) return;

    front--;
}

char top(){
    if(is_empty()) return ' ';
    return arr[front];
}

bool is_empty(){
    if(front == -1) return true;
    return false;
}

bool is_full(){
    if(front == STACK_LEN) return true;
    return false;
}

int size(){
    return front + 1;
}