#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define N 100
int g[N][N], mp[N], mc = INT_MAX;

void tsp(int n, int p[], int v[], int l, int c) {
    if (l == n) {
        c += g[p[l-1]][p[0]];
        if (c < mc) { mc = c; for(int i=0; i<n; i++) mp[i] = p[i]; }
        return;
    }
    for(int i=0; i<n; i++) {
        if (!v[i]) {
            v[i] = 1; p[l] = i;
            tsp(n, p, v, l+1, c + ((l>0) ? g[p[l-1]][i] : 0));
            v[i] = 0;
        }
    }
}

int main() {
    int sizes[] = {4, 5, 6, 7, 8, 9, 10};
    int ns = sizeof(sizes)/sizeof(sizes[0]);
    
    printf("Nodes\tTime(s)\n");
    for(int t=0; t<ns; t++) {
        int n = sizes[t];
        
        // Generate random graph
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                g[i][j] = (i==j) ? 0 : rand()%100+1;
        
        int p[N], v[N]={0};
        mc = INT_MAX;
        
        clock_t s = clock();
        p[0]=0; v[0]=1;
        tsp(n, p, v, 1, 0);
        clock_t e = clock();
        
        printf("%d\t%.4f\n", n, ((double)(e-s))/CLOCKS_PER_SEC);
    }
    return 0;
}