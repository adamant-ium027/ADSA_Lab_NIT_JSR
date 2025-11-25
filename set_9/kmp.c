#include <stdio.h>
#include <string.h>

void kmp(char *t, char *p) {
    int n=strlen(t), m=strlen(p), lps[m], i=1, len=0;
    lps[0]=0;

    while(i<m)
        if(p[i]==p[len]) lps[i++]=++len;
        else if(len) len=lps[len-1];
        else lps[i++]=0;

    i = len = 0;
    while(i<n) {
        if(t[i]==p[len]) i++, len++;
        if(len==m) printf("Match at %d\n", i-m), len=lps[len-1];
        else if(i<n && t[i]!=p[len]) len ? (len=lps[len-1]) : i++;
    }
}

int main() {
    kmp("ABABDABACDABABCABAB", "ABABCABAB");
}