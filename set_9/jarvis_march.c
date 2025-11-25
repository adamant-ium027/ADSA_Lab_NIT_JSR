#include <stdio.h>

typedef struct { int x, y; } P;

int cross(P a, P b, P c) {
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

int nextPoint(P p[], int n, int i) {
    int r = (i+1)%n;
    for(int j=0;j<n;j++)
        if(cross(p[i], p[r], p[j]) < 0) r = j;
    return r;
}

void jarvis(P p[], int n) {
    int hull[10000], h = 0;

    int left = 0;
    for(int i=1;i<n;i++)
        if(p[i].x < p[left].x) left = i;

    int cur = left;
    do {
        hull[h++] = cur;
        int nxt = nextPoint(p, n, cur);
        cur = nxt;
    } while(cur != left);

    printf("Convex Hull:\n");
    for(int i=0;i<h;i++)
        printf("(%d, %d)\n", p[hull[i]].x, p[hull[i]].y);
}

int main() {
    P p[]={{0,3},{2,2},{1,1},{2,1},{3,0},{0,0},{3,3}};
    int n = sizeof(p)/sizeof(p[0]);
    jarvis(p, n);
}