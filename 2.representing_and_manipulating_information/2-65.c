#include <stdio.h>
#include <stdlib.h>
#include "csapp2.h"

/* Return 1 when x contains an even number of 1s; 0 otherwise. Assume
 * w=32. */

int even_ones(unsigned x) {
    unsigned y = x >> 16;
    x ^= y;
    y = x >> 8;
    x ^= y;
    y = x >> 4;
    x ^= y;
    y = x >> 2;
    x ^= y;
    y = x >> 1;
    x ^= y;
    return (x & 0x1) == 0;
}


int main(int argc, char *argv[]) {
    unsigned val;
    if (argc == 1) {
        char *line = NULL;
        size_t lim = 0;
        if (getline(&line, &lim, stdin) > 0) {
            val = (unsigned) strtol(line, NULL, 0);
        }
    } else if (argc == 2) {
        val = (unsigned) strtol(*++argv, NULL, 0);
    } else {
        printf("Usage: 2-65.out [integer]");
        return -1;
    }
    int res = even_ones(val);
    
#ifdef DEBUG
    char s[100];
    /* printf("%u\n", val); */
    get_bits((byte_pointer) &val, sizeof(unsigned), s);
    printf("%u:\n%s\n%d\n", val, s, res);
#endif
    return res;
}
