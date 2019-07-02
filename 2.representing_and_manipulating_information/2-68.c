#include <stdio.h>
#include <stdlib.h>
#include "csapp2.h"

/* Make with least significant n bits set to 1. Examples: n = 6 -->
 * 0x3F, n = 17 --> 0x1FFFF. Assume 1 <= n <= w */

int lower_bits(int x, int n) {
    return x | (~0 >> (sizeof(unsigned) - n));
}

int main(int argc, char *argv[]) {
    int n, val = 0;

    if (argc < 2 || argc > 3) {
        printf("Usage: 2-68.out n [integer]\n");
        return -1;
    }

    n = strtol(*++argv, NULL, 0);
    if (n < 1 || n > (int) sizeof(int)*8) {
        printf("Invalid n: %d\n", n);
    }
    
    if (argc == 2) {
        char *line = NULL;
        size_t lim = 0;
        if (getline(&line, &lim, stdin) > 0) {
            n = strtol(line, NULL, 0);
        }
    } else {
        n = strtol(*++argv, NULL, 0);
    }

    int res = lower_bits(val, n);

    #ifdef DEBUG
    #endif
    printf("%")
}
