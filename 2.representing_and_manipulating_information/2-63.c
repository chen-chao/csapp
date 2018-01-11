#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "csapp2.h"

int sra(int x, int k) {
/* perform shift logically */
    int xsrl = (unsigned) x >> k;
    int w = 8*sizeof(int);
    /* bug here */
    unsigned hbit = (x & INT_MIN) == INT_MIN;
    unsigned mask = ((hbit << k) - hbit) << (w-k);
    return xsrl | mask;
}

int srl(int x, int k) {
/* perform shift arithmetically */
    int xsra = (int) x >> k;
    int w = 8*sizeof(int);
    unsigned mask = (1 << (w-k)) - 1;
    return xsra & mask;
}

void test(int x, int k) {
    int ashift, lshift, len;
    ashift = sra(x, k);
    lshift = srl(x, k);
    len = sizeof(int);
    
    char ss[100], as[100], ls[100];
    void get_bits(byte_pointer start, int len, char *s);

    get_bits((byte_pointer) &x, len, ss);
    get_bits((byte_pointer) &ashift, len, as);
    get_bits((byte_pointer) &lshift, len, ls);

    printf(">> %17d:\t%s\n%20s:\t%s\n%20s:\t%s\n", k, ss,
           "arithmetical shift", as, "logical shift", ls);
}


int main(int argc, char *argv[]) {
    test(INT_MIN, 1);
    test(INT_MIN, 6);
    test(INT_MIN, 31);
    test(INT_MAX, 1);
    test(INT_MAX, 15);
    test(INT_MAX, 31);
    test(0x123456, 1);
    test(0x123456, 15);
    test(0x123456, 31);
    test(-123456, 1);
    test(-123456, 15);
    return 0;
}
