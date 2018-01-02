#include <stdio.h>
#include <limits.h>

#ifdef DEBUG
#include "csapp2.h"
#endif

unsigned int_shifts_are_logical() {
    size_t w = sizeof(int) << 3;
    #ifdef DEBUG
        void show_bytes(byte_pointer bp, int len);
        unsigned tmp = INT_MIN >> (w-1);
        show_bytes((byte_pointer) &tmp, sizeof(unsigned));
    #endif
    return (INT_MIN >> (w-1)) & 0x1;
}

int main() {
    printf("%u\n", int_shifts_are_logical());
    return 0;
}
