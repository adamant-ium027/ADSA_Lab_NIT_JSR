#include <stdio.h>
#include <stdbool.h>
#define N 10

bool safe(int v, int g[][N], int c[], int col, int n) {
    for(int i=0; i<n; i++) 
        if(g[v][i] && c[i]==col) return false;
    return true;
}

bool color(int g[][N], int m, int c[], int v, int n) {
    if(v == n) return true;
    for(int col=1; col<=m; col++) {
        if(safe(v, g, c, col, n)) {
            c[v] = col;
            if(color(g, m, c, v+1, n)) return true;
            c[v] = 0;
        }
    }
    return false;
}

int main() {
    int g[N][N] = {{0,1,1},{1,0,1},{1,1,0}};
    int n = 3;
    
    for(int m=1; m<=n; m++) {
        int c[N] = {0};
        if(color(g, m, c, 0, n)) {
            printf("Min colors: %d\n", m);
            for(int i=0; i<n; i++) printf("%d:%d ", i, c[i]);
            break;
        }
    }
    
    printf("\n");
    return 0;
}