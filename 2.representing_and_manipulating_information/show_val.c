#include <stdio.h>
#include <stdlib.h>
#include "csapp2.h"

int main(int argc, char *argv[]) {
    void show_val(int);
    char *s;
    while (--argc > 0) {
        printf("%s:\n", s = *++argv);
        show_val(atoi(s));
    }
    return 0;
}
