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

void get_bit(byte_pointer bp, char *s) {
    for (int i = 7; i >= 0; *bp /= 2, i--) {
        s[i] = *bp % 2 + '0';
    }
    s[8] = '\0';
}

void get_bits(byte_pointer start, int len, char *s) {
    /* it's different between big endian and little endian machine */
    for (int i = 0; i < len; i++, s += 8){
        get_bit(start+i, s);
    }
}
