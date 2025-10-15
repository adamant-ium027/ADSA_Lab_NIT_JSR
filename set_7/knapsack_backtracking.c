#include <stdio.h>

#define MAX_ITEMS 100

int n;                    // number of items
int W;                    // maximum capacity
int weights[MAX_ITEMS];    // weights of items
int values[MAX_ITEMS];     // values of items

int maxValue = 0;          // store maximum value found
int bestSet[MAX_ITEMS];    // store items for maximum value
int currentSet[MAX_ITEMS]; // track current selection

void knapsack(int i, int currentWeight, int currentValue) {
    if (i == n) {
        // reached end, check if this is better
        if (currentValue > maxValue) {
            maxValue = currentValue;
            for (int k = 0; k < n; k++)
                bestSet[k] = currentSet[k];
        }
        return;
    }

    // Include the current item if it does not exceed capacity
    if (currentWeight + weights[i] <= W) {
        currentSet[i] = 1; // include item
        knapsack(i + 1, currentWeight + weights[i], currentValue + values[i]);
    }

    // Exclude the current item
    currentSet[i] = 0; // exclude item
    knapsack(i + 1, currentWeight, currentValue);
}

int main() {
    // Hardcoded inputs
    values[0] = 60; weights[0] = 10;
    values[1] = 100; weights[1] = 20;
    values[2] = 120; weights[2] = 30;
    n = 3;
    W = 50;

    // Initialize currentSet and bestSet
    for (int i = 0; i < n; i++) {
        currentSet[i] = 0;
        bestSet[i] = 0;
    }

    knapsack(0, 0, 0);

    // Print results
    printf("Maximum value: %d\n", maxValue);
    printf("Items included in the knapsack: ");
    for (int i = 0; i < n; i++) {
        if (bestSet[i] == 1)
            printf("%d ", i);
    }
    printf("\n");

    return 0;
}