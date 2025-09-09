// Implement a stack using two queues by Method-I (making Enqueue operation costly)

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Queue {
    int arr[MAX];
    int front, rear;
};

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = -1;
    return q;
}

int isEmpty(struct Queue* q) {
    return q->front == -1;
}

int isFull(struct Queue* q) {
    return (q->rear + 1) % MAX == q->front;
}

void enqueue(struct Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow\n");
        return;
    }
    if (q->front == -1) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->arr[q->rear] = value;
}

int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        return -1; // Underflow
    }
    int value = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1; // queue becomes empty
    } else {
        q->front = (q->front + 1) % MAX;
    }
    return value;
}

struct Stack {
    struct Queue* q1;
    struct Queue* q2;
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->q1 = createQueue();
    stack->q2 = createQueue();
    return stack;
}

// O(n) push
void push(struct Stack* stack, int value) {
    // Step 1: enqueue new element into q2
    enqueue(stack->q2, value);

    // Step 2: move everything from q1 to q2
    while (!isEmpty(stack->q1)) {
        enqueue(stack->q2, dequeue(stack->q1));
    }

    // Step 3: swap q1 and q2
    struct Queue* temp = stack->q1;
    stack->q1 = stack->q2;
    stack->q2 = temp;
}

// O(1) pop
int pop(struct Stack* stack) {
    if (isEmpty(stack->q1)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return dequeue(stack->q1);
}

int top(struct Stack* stack) {
    if (isEmpty(stack->q1)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->q1->arr[stack->q1->front];
}

int isStackEmpty(struct Stack* stack) {
    return isEmpty(stack->q1);
}

void printStack(struct Stack* stack) {
    if (isEmpty(stack->q1)) {
        printf("Stack is empty\n");
        return;
    }
    for (int i = stack->q1->front; ; i = (i + 1) % MAX) {
        printf("%d ", stack->q1->arr[i]);
        if (i == stack->q1->rear) break;
    }
    printf("\n");
}

int main() {
    struct Stack* stack = createStack();

    push(stack, 10);
    push(stack, 20);
    push(stack, 30);

    printf("Stack: ");
    printStack(stack);

    printf("Popped: %d\n", pop(stack));
    printf("Popped: %d\n", pop(stack));

    printf("Stack after pop: ");
    printStack(stack);

    printf("Top element: %d\n", top(stack));

    return 0;
}