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
    scanf("%d %d %d", &n, &e, &m);
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u][v] = G[v][u] = 1;
    }

    if (dfs(0, 0)) printf("Clique found\n");
    else printf("No clique\n");

    return 0;
}