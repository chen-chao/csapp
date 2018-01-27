#include <stdio.h>
#include <stdlib.h>
#include "csapp2.h"


/* Do rotate right shift. Assume 0 <= n < w, Examples when x =
 * 0x12345678 and w = 32: n=4 -> 0x81234567, n=20 -> 0x45678123 */

unsigned rotate_right(unsigned x, int n) {
    int w = sizeof(unsigned) << 3;
    if (n < 0 || n >= w)
        return -1;
    unsigned mask = (1 << n) - 1;
    return (x >> n) | ((x & mask) << (w-n));
}

void print_rr(unsigned x, int n) {
    printf("%u -> %d\n", x, n);
    int len = sizeof(unsigned);
    unsigned res = rotate_right(x, n);
    show_bytes((byte_pointer) &x, len);
    show_bytes((byte_pointer) &res, len);
}

int main(int argc, char *argv[]) {
#ifdef DEBUG
    print_rr(0x12345678, 16);
    print_rr(0x87654321, 4);
    print_rr(0x654321, 0);
    print_rr(0x12345678, 31);
    return 0;
#endif
    if (argc != 3)
        return -1;
    unsigned x;
    int n;
    x = (unsigned) strtol(*++argv, NULL, 0);
    n = (int) strtol(*++argv, NULL, 0);
    print_rr(x, n) ;
    return 0;
}
