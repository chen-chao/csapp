#include <stdio.h>
#include <limits.h>
#include "csapp2.h"


void show_bytes(byte_pointer bp, int len);

unsigned unsigned_high_prod(unsigned x, unsigned y) {
    size_t halfw = sizeof(unsigned) << 2;
    unsigned mask = ~(INT_MIN >> (halfw-1));
    unsigned low_x = x & mask;
    unsigned low_y = y & mask;
    unsigned high_x = x >> halfw;
    unsigned high_y = y >> halfw;
#ifdef DEBUG
    unsigned htmp = high_x*high_y;
    printf("h part:");
    show_bytes((byte_pointer) &htmp, sizeof(unsigned));
    unsigned ltmp = low_x*high_y + low_y*high_x;
    unsigned rtmp = ltmp >> halfw;
    show_bytes((byte_pointer) &rtmp, sizeof(unsigned));
#endif
    return high_x*high_y + ((low_x*high_y + low_y*high_x) >> halfw);
}

int int_high_prod(int x, int y) {
    size_t w = sizeof(int) << 3;
    unsigned ux, uy, hbit_x, hbit_y; 
    ux = (unsigned) x;
    uy = (unsigned) y;
    hbit_x = ux >> (w-1);
    hbit_y = uy >> (w-1);
    return (int) (unsigned_high_prod(ux, uy)-(hbit_x*uy + hbit_y*ux));
}

unsigned long long unsigned_long_prod(unsigned x, unsigned y) {
    return (unsigned long long) x * (unsigned long long) y;
}

long long int long_int_prod(int x, int y) {
    return (long long int) x * (long long int) y;
}

void print_prod(int x, int y){
    unsigned ux, uy, ures;
    unsigned long long ulres;
    ux = x;
    uy = y;
    ures = unsigned_high_prod(ux, uy);
    ulres = unsigned_long_prod(ux, uy);
    printf("unsigned_high_prod gives result:");
    show_bytes((byte_pointer) &ures, sizeof(unsigned));
    printf("unsigned_long_prod gives result:");
    show_bytes((byte_pointer) &ulres, sizeof(unsigned long long));
    printf("\n");
    int ires;
    long long int lires;
    ires = int_high_prod(x, y);
    lires = long_int_prod(x, y);
    printf("int_high_prod gives result:");
    show_bytes((byte_pointer) &ires, sizeof(int));
    printf("long_int_prod gives result:");
    show_bytes((byte_pointer) &lires, sizeof(long long int));
}

int main(int argc, char *argv[]) {
#ifdef DEBUG
    print_prod(INT_MIN, INT_MAX);
    printf("\n");
    print_prod(0x12345678, 0x87654321);
    printf("\n");
    print_prod(1234567890, -876543210);
    return 0;
#endif
    unsigned parse_value(char *s);
    if (argc != 3) {
        printf("Argument number should be 3, current %d\n", argc);
        return -1;
    }
    int x = parse_value(*++argv);
    int y = parse_value(*++argv);
    print_prod(x, y);
    return 0;
}
