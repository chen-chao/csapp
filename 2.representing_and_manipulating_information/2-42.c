#include <stdio.h>
#include <limits.h>

int div16(int x) {
    int signbit = ((unsigned) x & INT_MIN) >> 31;
    return (x + (signbit << 4) - signbit) >> 4;
}

int div16_from_book(int x) {
    int bias = (x >> 31) & 0xF;
    return (x + bias) >> 4;
}

int main() {
    printf("%d / 16 = %d\n", INT_MIN, div16(INT_MIN));
    printf("%d / 16 = %d\n", INT_MAX, div16(INT_MAX));
    for (int i = 0; i < 19; i++) {
        printf("%d / 16 = %d\n", i, div16(i));
        printf("%d / 16 = %d\n", -i, div16(-i));
    }
    return 0;
}
