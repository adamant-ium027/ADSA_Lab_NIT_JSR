#include <stdio.h>

#define N 6

void topoSort(int g[][N]) {
    int ind[N] = {0}, q[N], f = 0, r = -1, res[N], idx = 0;
    
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (g[i][j]) ind[j]++;
    
    for (int i = 0; i < N; i++)
        if (ind[i] == 0) q[++r] = i;
    
    while (f <= r) {
        int u = q[f++];
        res[idx++] = u;
        for (int v = 0; v < N; v++)
            if (g[u][v] && --ind[v] == 0)
                q[++r] = v;
    }
    
    if (idx != N) printf("Cycle detected!\n");
    else for (int i = 0; i < N; i++) printf("%d ", res[i]);
    printf("\n");
}

int main() {
    int g[N][N] = {{0}};
    g[5][2]=1; g[5][0]=1; g[4][0]=1; 
    g[4][1]=1; g[2][3]=1; g[3][1]=1;
    topoSort(g);
    return 0;
}