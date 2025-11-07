#include <stdio.h>
#include <stdlib.h>

typedef struct { int id, p, d; } Job;

int cmp(const void* a, const void* b) {
    return ((Job*)b)->p - ((Job*)a)->p;
}

int main() {
    Job j[] = {{1,20,2},{2,15,2},{3,10,1},{4,5,3}};
    int n = 4;
    
    qsort(j, n, sizeof(Job), cmp);
    
    int md = 0;
    for(int i=0; i<n; i++) if(j[i].d > md) md = j[i].d;
    
    int r[md+1], tp=0, jc=0;
    for(int i=0; i<=md; i++) r[i]=0;
    
    for(int i=0; i<n; i++) {
        for(int k=j[i].d; k>0; k--) {
            if(!r[k]) {
                r[k] = j[i].id;
                tp += j[i].p;
                jc++;
                break;
            }
        }
    }
    
    printf("Jobs: ");
    for(int i=1; i<=md; i++) if(r[i]) printf("J%d ", r[i]);
    printf("\nProfit: %d\nCount: %d\n", tp, jc);
    return 0;
}