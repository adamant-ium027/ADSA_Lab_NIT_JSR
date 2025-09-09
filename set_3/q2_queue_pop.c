// Implement a queue using two stacks using Method-II (making Pop operation costly).

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Stack {
    int arr[MAX];
    int top;
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

int isFull(struct Stack* stack) {
    return stack->top == MAX - 1;
}

void push(struct Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
}

int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        return -1; // Underflow
    }
    return stack->arr[stack->top--];
}

struct Queue {
    struct Stack* s1;
    struct Stack* s2;
};

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->s1 = createStack();
    q->s2 = createStack();
    return q;
}

// O(1) enqueue
void enQueue(struct Queue* q, int value) {
    push(q->s1, value);
}

// O(n) dequeue
int deQueue(struct Queue* q) {
    if (isEmpty(q->s1)) {
        printf("Queue Underflow\n");
        return -1;
    }

    // Move all from s1 to s2
    while (!isEmpty(q->s1)) {
        push(q->s2, pop(q->s1));
    }

    // Pop from s2 (front of queue)
    int front = pop(q->s2);

    // Move everything back to s1
    while (!isEmpty(q->s2)) {
        push(q->s1, pop(q->s2));
    }

    return front;
}

void printQueue(struct Queue* q) {
    if (isEmpty(q->s1)) {
        printf("Queue is empty\n");
        return;
    }
    for (int i = 0; i <= q->s1->top; i++) {
        printf("%d ", q->s1->arr[i]);
    }
    printf("\n");
}

int main() {
    struct Queue* q = createQueue();

    enQueue(q, 10);
    enQueue(q, 20);
    enQueue(q, 30);

    printf("Queue: ");
    printQueue(q);

    printf("Dequeued: %d\n", deQueue(q));
    printf("Dequeued: %d\n", deQueue(q));

    printf("Queue after dequeue: ");
    printQueue(q);

    return 0;
}