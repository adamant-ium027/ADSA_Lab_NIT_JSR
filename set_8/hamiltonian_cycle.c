#include <stdio.h>

#define N 6

int G[N][N] = {0};
int path[N];
int used[N];

int dfs(int pos) {
    if (pos == N)
        return G[path[N-1]][path[0]];

    for (int v = 1; v < N; v++) {
        if (!used[v] && G[path[pos-1]][v]) {
            used[v] = 1;
            path[pos] = v;

            if (dfs(pos + 1))
                return 1;

            used[v] = 0;
        }
    }
    return 0;
}

int main() {
    int e = 7;
    int edges[][2] = {
        {0,1}, {1,2}, {2,3},
        {3,4}, {4,5}, {5,0},
        {1,5}
    };

    for (int i = 0; i < e; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        G[u][v] = G[v][u] = 1;
    }

    path[0] = 0;
    used[0] = 1;

    if (dfs(1))
        printf("Hamiltonian cycle exists\n");
    else
        printf("No Hamiltonian cycle\n");

    return 0;
}