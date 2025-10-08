// Implement Kruskal's algorithm for the minimum spanning tree problem.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 5  // number of vertices

struct Edge {
    int src, dest, weight;
};

struct subset {
    int parent, rank;
};

// Find set of element i (path compression)
int find(struct subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union of two sets (by rank)
void Union(struct subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare function for qsort (ascending by weight)
int compare(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

void KruskalMST(int graph[V][V]) {
    struct Edge edges[V * V];
    int eCount = 0;

    // Step 1: Convert adjacency matrix to edge list
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) { // upper triangle to avoid duplicates
            if (graph[i][j] != 0 && graph[i][j] != INT_MAX) {
                edges[eCount].src = i;
                edges[eCount].dest = j;
                edges[eCount].weight = graph[i][j];
                eCount++;
            }
        }
    }

    // Step 2: Sort edges by weight
    qsort(edges, eCount, sizeof(edges[0]), compare);

    // Step 3: Create subsets for union-find
    struct subset* subsets = (struct subset*)malloc(V * sizeof(struct subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Step 4: Build MST
    struct Edge result[V];  // stores MST edges
    int e = 0;              // number of edges in MST
    int i = 0;              // index for sorted edges

    while (e < V - 1 && i < eCount) {
        struct Edge next = edges[i++];

        int x = find(subsets, next.src);
        int y = find(subsets, next.dest);

        if (x != y) {
            result[e++] = next;
            Union(subsets, x, y);
        }
    }

    // Step 5: Print the MST
    printf("Edge \tWeight\n");
    for (i = 0; i < e; i++)
        printf("%d - %d \t%d\n", result[i].src, result[i].dest, result[i].weight);

    free(subsets);
}

int main() {
    // Example adjacency matrix
    // 0 means no edge; INT_MAX can also be used for "no edge"
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    KruskalMST(graph);
    return 0;
}