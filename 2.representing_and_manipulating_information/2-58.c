#include <stdio.h>

unsigned is_little_endian() {
    unsigned a = 0x1;
    return *((unsigned char *) &a);
}

int main() {
    printf("%u\n", is_little_endian());
    return 0; 
}
