#include <stdio.h>
#include <string.h>

size_t strlen(const char *s);

/* Determin whether stirng s is longer than string t */
/* WARNING: this function is buggy */

int strlonger(char *s, char *t) {
    return strlen(s) - strlen(t) > 0;
}

int main() {
    char s[] = "12345";
    char t[] = "1234567";
    printf("%s is longer than %s: %d\n", s, t, strlonger(s, t));
    return 0;
}
