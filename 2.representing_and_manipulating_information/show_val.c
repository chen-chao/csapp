#include <stdio.h>
#include <stdlib.h>

void show_int(int);
void show_float(float);
void show_pointer(void *);

void show_val(int val) {
    int ival = val;
    float fval = (float) ival;
    int *pval = &ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}

int main(int argc, char *argv[]) {
    char *s;
    while (--argc > 0) {
        printf("%s:\n", s = *++argv);
        show_val(atoi(s));
    }
    return 0;
}
