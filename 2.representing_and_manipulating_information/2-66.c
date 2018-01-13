#include <stdio.h>
#include <stdlib.h>
#include "csapp2.h"

/* Generate mask indicating leftmost 1 in x. Assume w=32. For example
 * 0xFF00 -> 0x8000, and 0x6600 -> 0x4000. If x = 0, then return 0 */

int leftmost_ones(unsigned x) {
    /* x -> [ 0 0 0 ... 1 1 1] */
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    return x - (x >> 1);
}

int main(int argc, char *argv[]) {
    unsigned val;
    char *s = NULL;
    size_t lim = 0;
    if (argc == 1 && getline(&s, &lim, stdin) > 0)
        val = (unsigned) strtol(s, NULL, 0);
    else if (argc == 2)
        val = (unsigned) strtol(*++argv, NULL, 0);
    else
        return -1;
    printf("leftmost 1 of %d:\n", val);
    show_bytes((byte_pointer) &val, sizeof(unsigned));

    int leftmost = leftmost_ones(val);
    show_bytes((byte_pointer) &leftmost, sizeof(int));

    return 0;
}
