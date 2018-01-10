/* Finds out the common part in the binary strings of an integer and
 * its equivalent float */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csapp2.h"

#define MAXLEN 100

int longest_substring(char *s, char *t, int *sstart, int *tstart) {
    int m = strlen(s)+1;
    int n = strlen(t)+1;
    int mat[m][n];
    int i, j;
    for(i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            mat[i][j] = 0;
        }
    }
    int maxi, maxj, max = 0;
    for (i = 1; i < m; i++) {
        for (j = 1; j < n; j++) {
            if (s[i-1] == t[j-1]) {
                mat[i][j] = mat[i-1][j-1] +1;
            }
            if (mat[i][j] > max) {
                max = mat[i][j];
                maxi = i;
                maxj = j;
            }
        }
    }
    /* because both i,j start from 1, here no needs to +1 */
    *sstart = maxi-max;
    *tstart = maxj-max;
    return max;
}

void align_print(char *s, char *t, int m, int n, int len) {
    int i;
    int delta = m-n;

    for (i = 0; i < -delta; i++) {
        printf(" ");
    }
    printf("%s\n", s);
    int starp = (delta > 0 ? m:n);
    for (i = 0; i < starp; i++) {
        printf(" ");
    }
    for (; i < starp+len; i++) {
        printf("*");
    }
    printf("\n");
    for (i = 0; i < delta; i++) {
        printf(" ");
    }
    printf("%s\n", t);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("invalid argument number: %d\n", argc);
        return -1;
    }
    int ival = (int) strtol(*++argv, NULL, 0);
    float dval = ival;
    char s[MAXLEN], t[MAXLEN];
    get_bits((byte_pointer) &ival, sizeof(int), s);
    get_bits((byte_pointer) &dval, sizeof(float), t);
    int maxlen, sstart, tstart;
    maxlen = longest_substring(s, t, &sstart, &tstart);
    align_print(s, t, sstart, tstart, maxlen);
    return 0;
}
