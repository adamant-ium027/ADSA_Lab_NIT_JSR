// Write a function to identify the largest and smallest cycles in a given directed or undirected graph.

#include <stdio.h>
#include <string.h>

#define V 6

int graph[V][V];
int visited[V];
int path[V];
int path_index = 0;
int smallest_cycle = 1e9, largest_cycle = -1;

void printCycle(int cycle[], int len) {
    for (int i = 0; i < len; i++)
        printf("%d ", cycle[i]);
    printf("%d\n", cycle[0]); // close the cycle
}

void dfs(int start, int u, int isDirected) {
    visited[u] = 1;
    path[path_index++] = u;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            // Ignore reverse edge in undirected graph
            if (!isDirected && path_index > 1 && v == path[path_index - 2])
                continue;

            if (!visited[v]) {
                dfs(start, v, isDirected);
            } else if (v == start) {
                // Found a cycle
                int len = path_index;
                if (len > 1) {
                    if (len < smallest_cycle) smallest_cycle = len;
                    if (len > largest_cycle) largest_cycle = len;

                    printf("Cycle of length %d: ", len);
                    printCycle(path, len);
                }
            }
        }
    }

    path_index--;
    visited[u] = 0;
}

void findCycles(int isDirected) {
    smallest_cycle = 1e9;
    largest_cycle = -1;

    for (int i = 0; i < V; i++) {
        memset(visited, 0, sizeof(visited));
        path_index = 0;
        dfs(i, i, isDirected);
    }

    if (largest_cycle == -1)
        printf("\nNo cycles found.\n");
    else {
        printf("\nSmallest cycle length: %d\n", smallest_cycle);
        printf("Largest cycle length: %d\n", largest_cycle);
    }
}

int main() {
    // Example directed graph
    int adj[V][V] = {
        {0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0},
        {1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0}
    };

    // Copy adjacency matrix
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = adj[i][j];

    printf("Finding cycles in Directed Graph:\n");
    findCycles(1); // 1 for directed, 0 for undirected

    return 0;
}