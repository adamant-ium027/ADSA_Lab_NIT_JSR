// Implement DFS algorithm for grpahs. Your function should be able to identify all the tree edges,
// back edges, forward edges and cross edges.

#include <stdio.h>

#define V 6

enum { WHITE, GRAY, BLACK };

int time_counter = 0;
int graph[V][V];
int color[V], parent[V], disc[V], finish[V];

void dfs_visit(int u) {
    color[u] = GRAY;
    disc[u] = ++time_counter;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) { // if edge exists
            if (color[v] == WHITE) {
                printf("Tree Edge: (%d -> %d)\n", u, v);
                parent[v] = u;
                dfs_visit(v);
            } 
            else if (color[v] == GRAY) {
                printf("Back Edge: (%d -> %d)\n", u, v);
            } 
            else if (color[v] == BLACK) {
                if (disc[u] < disc[v])
                    printf("Forward Edge: (%d -> %d)\n", u, v);
                else
                    printf("Cross Edge: (%d -> %d)\n", u, v);
            }
        }
    }

    color[u] = BLACK;
    finish[u] = ++time_counter;
}

void DFS() {
    for (int i = 0; i < V; i++) {
        color[i] = WHITE;
        parent[i] = -1;
    }

    for (int i = 0; i < V; i++)
        if (color[i] == WHITE)
            dfs_visit(i);
}

int main() {
    // Example Directed Graph (Adjacency Matrix)
    int adj[V][V] = {
        {0, 1, 1, 0, 0, 0}, // 0 -> 1,2
        {0, 0, 0, 1, 0, 0}, // 1 -> 3
        {0, 0, 0, 1, 1, 0}, // 2 -> 3,4
        {0, 0, 0, 0, 0, 1}, // 3 -> 5
        {0, 0, 0, 1, 0, 0}, // 4 -> 3
        {0, 0, 0, 0, 0, 0}  // 5
    };

    // copy graph
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = adj[i][j];

    printf("DFS Edge Classification:\n\n");
    DFS();

    printf("\nDiscovery and Finishing Times:\n");
    for (int i = 0; i < V; i++)
        printf("Vertex %d: disc=%d, finish=%d\n", i, disc[i], finish[i]);

    return 0;
}