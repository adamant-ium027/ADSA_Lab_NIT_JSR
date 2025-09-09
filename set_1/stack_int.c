#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define STACK_LEN 101

void push_i(int);
void pop_i();
char top_i();
bool is_empty_i();
bool is_full_i();
int size_i();

int arr_i[STACK_LEN];
int front_i = -1;

void push_i(int item){
    if(is_full_i()) return;

    arr_i[++front_i] = item;
}

void pop_i(){
    if(is_empty_i()) return;

    front_i--;
}

char top_i(){
    if(is_empty_i()) return ' ';
    return arr_i[front_i];
}

bool is_empty_i(){
    if(front_i == -1) return true;
    return false;
}

bool is_full_i(){
    if(front_i == STACK_LEN) return true;
    return false;
}

int size_i(){
    return front_i + 1;
}