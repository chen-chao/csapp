#include <stdio.h>

int int_size_is_32() {
    return ((1 << 15) << 1) != 0 && (1 << 31) != 0 && ((1 << 31) << 1) == 0;
}

int main() {
    int res = int_size_is_32();
    printf("%d\n", res);
    return res;
}
