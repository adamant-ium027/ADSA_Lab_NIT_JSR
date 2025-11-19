#include <stdio.h>

#define N 6

int G[N][N] = {0};
int color[N];

int dfs(int v, int c) {
    color[v] = c;

    for (int u = 0; u < N; u++) {
        if (G[v][u]) {
            if (color[u] == -1) {
                if (!dfs(u, 1 - c)) return 0;
            }
            else if (color[u] == c) return 0;
        }
    }
    return 1;
}

int main() {
    int e = 6;
    int edges[][2] = {
        {0,1}, {1,2}, {2,3},
        {3,4}, {4,5}, {5,0}
    };

    for (int i = 0; i < e; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        G[u][v] = G[v][u] = 1;
    }

    for (int i = 0; i < N; i++)
        color[i] = -1;

    for (int i = 0; i < N; i++) {
        if (color[i] == -1) {
            if (!dfs(i, 0)) {
                printf("Graph is NOT bipartite\n");
                return 0;
            }
        }
    }

    printf("Graph is bipartite\n");
    return 0;
}