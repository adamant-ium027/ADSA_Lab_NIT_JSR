#include <stdio.h>
#include <string.h>

#define d 256
#define q 101

void rabinKarp(char *txt, char *pat) {
    int n = strlen(txt), m = strlen(pat);
    int h = 1, p = 0, t = 0;

    for (int i = 0; i < m - 1; i++) h = (h * d) % q;

    for (int i = 0; i < m; i++) {
        p = (d * p + (unsigned char)pat[i]) % q;
        t = (d * t + (unsigned char)txt[i]) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (p == t && !strncmp(txt + i, pat, m))
            printf("Match at index %d\n", i);

        if (i < n - m) {
            t = (d * (t - (unsigned char)txt[i] * h)
                 + (unsigned char)txt[i + 1]) % q;
            if (t < 0) t += q;
        }
    }
}

int main() {
    rabinKarp("GCTAGCTCTACG", "GCT");
}