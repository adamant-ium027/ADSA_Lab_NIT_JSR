#include <stdio.h>

int G[30][30];   // adjacency matrix
int n, e, m;
int comb[30];

int check_clique(int k) {
    for (int i = 0; i < m; i++)
        for (int j = i + 1; j < m; j++)
            if (!G[comb[i]][comb[j]])
                return 0;
    return 1;
}

int dfs(int idx, int start) {
    if (idx == m) return check_clique(m);

    for (int v = start; v < n; v++) {
        comb[idx] = v;
        if (dfs(idx + 1, v + 1))
            return 1;
    }
    return 0;
}

int main() {
    n = 5; // number of vertices
    e = 6; // number of edges
    m = 3; // clique size to check

    int edges[6][2] = {
        {0, 1},
        {1, 2},
        {2, 3},
        {0, 2},
        {1, 3},
        {3, 4}
    };

    for (int i = 0; i < e; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        G[u][v] = G[v][u] = 1;
    }

    if (dfs(0, 0)) printf("Clique found\n");
    else printf("No clique\n");

    return 0;
}