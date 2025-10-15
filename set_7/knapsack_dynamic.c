#include <stdio.h>

#define MAX_ITEMS 100
#define MAX_CAPACITY 1000

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    // Hardcoded inputs
    int values[] = {60, 100, 120};   // values of items
    int weights[] = {10, 20, 30};    // weights of items
    int n = sizeof(values) / sizeof(values[0]); // number of items
    int W = 50;                      // maximum capacity of knapsack

    int dp[n + 1][W + 1];

    // Build table dp[][] in bottom-up manner
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    printf("Maximum value that can be put in knapsack of capacity %d is %d\n", W, dp[n][W]);

    // Optional: print selected items
    printf("Items included in the knapsack: ");
    int w = W;
    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            printf("%d ", i - 1); // item index
            w -= weights[i - 1];
        }
    }
    printf("\n");

    return 0;
}