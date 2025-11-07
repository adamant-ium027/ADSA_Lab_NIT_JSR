#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct Node { 
    int v; 
    struct Node* n; 
} Node;

typedef struct Graph { 
    int v; 
    Node** a; 
    bool d; 
} Graph;

Graph* createGraph(int v, bool d) {
    Graph* g = malloc(sizeof(Graph));
    g->v = v; 
    g->d = d;
    g->a = calloc(v, sizeof(Node*));
    return g;
}

void addEdge(Graph* g, int s, int d) {
    Node* n = malloc(sizeof(Node));
    n->v = d; 
    n->n = g->a[s]; 
    g->a[s] = n;
    if (!g->d) { 
        n = malloc(sizeof(Node));
        n->v = s; 
        n->n = g->a[d]; 
        g->a[d] = n;
    }
}

void freeGraph(Graph* g) {
    for (int i = 0; i < g->v; i++) {
        Node* current = g->a[i];
        while (current) {
            Node* temp = current;
            current = current->n;
            free(temp);
        }
    }
    free(g->a);
    free(g);
}

// First DFS for SCC
void dfs1(Graph* gr, int u, bool vis[], int st[], int* top) {
    vis[u] = true;
    for(Node* t = gr->a[u]; t; t = t->n) 
        if(!vis[t->v]) 
            dfs1(gr, t->v, vis, st, top);
    st[++(*top)] = u;
}

// Second DFS for SCC
void dfs2(Graph* tr, int u, bool vis[]) {
    vis[u] = true; 
    printf("%d ", u);
    for(Node* t = tr->a[u]; t; t = t->n) 
        if(!vis[t->v]) 
            dfs2(tr, t->v, vis);
}

// Strongly Connected Components
void scc(Graph* gr) {
    printf("SCC: ");
    bool vis[MAX] = {0};
    int st[MAX], top = -1;
    
    for(int i = 0; i < gr->v; i++) 
        if(!vis[i]) 
            dfs1(gr, i, vis, st, &top);
    
    // Transpose graph
    Graph* tr = createGraph(gr->v, true);
    for(int i = 0; i < gr->v; i++)
        for(Node* t = gr->a[i]; t; t = t->n)
            addEdge(tr, t->v, i);
    
    bool v2[MAX] = {0};
    while(top >= 0) {
        int u = st[top--];
        if(!v2[u]) { 
            dfs2(tr, u, v2); 
            printf("| "); 
        }
    }
    printf("\n");
    freeGraph(tr);
}

// DFS for Articulation Points
void dfsAP(Graph* g, int u, bool vis[], bool isAP[], int dis[], int low[], int par[], int* time) {
    vis[u] = true;
    dis[u] = low[u] = ++(*time);
    int children = 0;
    
    for(Node* t = g->a[u]; t; t = t->n) {
        int v = t->v;
        if(!vis[v]) {
            children++; 
            par[v] = u; 
            dfsAP(g, v, vis, isAP, dis, low, par, time);
            
            low[u] = low[u] < low[v] ? low[u] : low[v];
            
            if(par[u] == -1 && children > 1) 
                isAP[u] = true;
            if(par[u] != -1 && low[v] >= dis[u]) 
                isAP[u] = true;
        } else if(v != par[u]) 
            low[u] = low[u] < dis[v] ? low[u] : dis[v];
    }
}

// Articulation Points
void ap(Graph* g) {
    printf("AP: ");
    bool vis[MAX] = {0}, isAP[MAX] = {0};
    int dis[MAX] = {0}, low[MAX] = {0}, par[MAX];
    int time = 0;
    
    for(int i = 0; i < g->v; i++) 
        par[i] = -1;
    
    for(int i = 0; i < g->v; i++) 
        if(!vis[i]) 
            dfsAP(g, i, vis, isAP, dis, low, par, &time);
    
    bool found = false;
    for(int i = 0; i < g->v; i++) 
        if(isAP[i]) {
            printf("%d ", i);
            found = true;
        }
    if (!found) printf("None");
    printf("\n");
}

// DFS for Bridges
void dfsBridge(Graph* g, int u, bool vis[], int dis[], int low[], int par[], int* time) {
    vis[u] = true;
    dis[u] = low[u] = ++(*time);
    
    for(Node* t = g->a[u]; t; t = t->n) {
        int v = t->v;
        if(!vis[v]) {
            par[v] = u; 
            dfsBridge(g, v, vis, dis, low, par, time);
            
            low[u] = low[u] < low[v] ? low[u] : low[v];
            if(low[v] > dis[u]) 
                printf("(%d,%d) ", u, v);
        } else if(v != par[u]) 
            low[u] = low[u] < dis[v] ? low[u] : dis[v];
    }
}

// Bridges
void br(Graph* g) {
    printf("Bridges: ");
    bool vis[MAX] = {0};
    int dis[MAX] = {0}, low[MAX] = {0}, par[MAX];
    int time = 0;
    
    for(int i = 0; i < g->v; i++) 
        par[i] = -1;
    
    for(int i = 0; i < g->v; i++) 
        if(!vis[i]) 
            dfsBridge(g, i, vis, dis, low, par, &time);
    printf("\n");
}

int main() {
    Graph* dg = createGraph(5, true);
    addEdge(dg, 0, 2); 
    addEdge(dg, 2, 1); 
    addEdge(dg, 1, 0);
    addEdge(dg, 0, 3); 
    addEdge(dg, 3, 4);
    
    scc(dg); 
    ap(dg); 
    br(dg);
    
    freeGraph(dg);
    return 0;
}