#include <stdio.h>
#include "csapp2.h"

unsigned replace_byte(unsigned x, unsigned char b, int i) {
    /* this is a private x_ copied from the argument x */
    byte_pointer bp = (byte_pointer) &x;
    if ((unsigned) i < sizeof(unsigned)) {
        /* changing the value pointed by bp does not affect the original x */
        *(bp+i) = b;
    }
    /* return the private x_ */
    return x;
}

int main() {
    void show_bytes(byte_pointer bp, int n);
    unsigned x = 0x12345678;
    unsigned char b = 0xAB;
    unsigned res;
    printf("%d: ", 2);
    res = replace_byte(x, b, 2);
    show_bytes((byte_pointer) &res, sizeof(unsigned));
    printf("%d: ", 0);
    res = replace_byte(x, b, 0);
    show_bytes((byte_pointer) &res, sizeof(unsigned));
    return 0;
}
