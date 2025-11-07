#include <stdio.h>

void coinChange(int c[], int n, int a) {
    int r = a, t = 0;
    printf("Amount: %d\nCoins: ", a);
    for(int i=0; i<n; i++) printf("%d ", c[i]);
    printf("\n");
    
    for(int i=0; i<n && r>0; i++) {
        int cnt = r / c[i];
        if(cnt > 0) {
            printf("Use %d of %d\n", cnt, c[i]);
            t += cnt;
            r -= cnt * c[i];
        }
    }
    printf("Total coins: %d\n", t);
    if(r > 0) printf("Remaining: %d\n", r);
}

int main() {
    int coins[] = {25, 10, 5, 1};
    int n = 4, amount = 67;
    coinChange(coins, n, amount);
    return 0;
}