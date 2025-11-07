#include <stdio.h>
#include <limits.h>

#define V 5
#define INF INT_MAX

void bellmanFord(int graph[V][V], int src) {
    int dist[V];

    // Step 1: Initialize distances
    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[src] = 0;

    // Step 2: Relax all edges |V|-1 times
    for (int k = 0; k < V - 1; k++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (graph[u][v] != INF && dist[u] != INF &&
                    dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }

    // Step 3: Check for negative-weight cycles
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != INF && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                printf("\nGraph contains a negative weight cycle!\n");
                return;
            }
        }
    }

    // Step 4: Print result
    printf("\nVertex\tDistance from Source (%d)\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            printf("%d\tINF\n", i);
        else
            printf("%d\t%d\n", i, dist[i]);
    }
}

int main() {
    // Hardcoded adjacency matrix (INF means no direct edge)
    int graph[V][V] = {
        {0,   -1,   4,  INF,  INF},
        {INF,  0,   3,   2,   2},
        {INF, INF,  0,  INF,  INF},
        {INF,  1,   5,   0,  INF},
        {INF, INF, INF,  -3,   0}
    };

    printf("Adjacency Matrix (INF = no edge):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] == INF)
                printf("%6s", "INF");
            else
                printf("%6d", graph[i][j]);
        }
        printf("\n");
    }

    int src = 0; // source vertex
    bellmanFord(graph, src);

    return 0;
}