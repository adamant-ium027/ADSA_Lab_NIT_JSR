#include <stdio.h>
#include <string.h>

void bm(char *t, char *p) {
    int n=strlen(t), m=strlen(p), bc[256], i, j;
    for (i=0;i<256;i++) bc[i]=m;
    for (i=0;i<m-1;i++) bc[(unsigned char)p[i]]=m-1-i;

    i=0;
    while(i<=n-m) {
        for(j=m-1;j>=0 && p[j]==t[i+j]; j--);
        if(j<0) printf("Match at %d\n", i), i+=bc[(unsigned char)t[i+m-1]];
        else i+=bc[(unsigned char)t[i+j]];
    }
}

int main() {
    bm("ABAAABCD", "ABC");
}