#include <stdio.h>
#include "csapp2.h"

void show_bytes(byte_pointer start, int len) {
    int i;
    for (i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) x, sizeof(void *));
}

void show_val(int val) {
    int ival = val;
    float fval = (float) ival;
    int *pval = &ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}

unsigned is_little_endian() {
    unsigned a = 0x1;
    return *((unsigned char *) &a);
}

void get_bit(byte_pointer bp, char *s) {
    unsigned val = *bp;
    for (int i = 7; i >= 0; val /= 2, i--) {
        s[i] = val % 2 + '0';
    }
    s[8] = '\0';
}

void get_bits(byte_pointer start, int len, char *s) {
    int little_endian = is_little_endian();
    byte_pointer bp = little_endian == 1 ? start+len-1 : start;
    int delta = little_endian == 1 ? -1 : 1;

    for (int i = 0; i < len; i++, s += 8, bp += delta)  {
        get_bit(bp, s);
    }
}
