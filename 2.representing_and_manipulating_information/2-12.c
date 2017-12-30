#include <stdio.h>
#include "csapp2.h"
#include <ctype.h>

#define BASE 16
#define MAXLEN 100

unsigned set_high_byte_zero(unsigned x) {
    return x & 0xFF;
}

unsigned set_high_byte_complement(unsigned x) {
    return x ^ ~(0xFF);
}

unsigned set_last_byte_one(unsigned x) {
    return x | 0xFF;
}

int htoi(char s[]){
    int i = 0;

    if (s[0] == '\0'){
        return -1;                
    }

    if (s[0] == '0') {
        i++;
        if (s[1] == '\0'){
            return 0;
        } else if (s[i] == 'x' || s[i] == 'X'){
            i++;
        } 
    }

    int val, alpha;
    val = 0;
    for (; s[i] != '\0'; i++){
        val *= BASE;
        if (isdigit(s[i])){
            val += s[i]-'0';
        } else if (isalpha(s[i])){
            alpha = toupper(s[i])-'A'+10;
            if (alpha >= BASE)
                return -1;
            val += alpha;
        } else {
            return -1;
        }
    }

    return val;
}


int main(int argc, char *argv[]) {
    void show_bytes(byte_pointer, int);
    unsigned val, bits;
    while (--argc > 0) {
        printf("%s:\n", *++argv);
        val = htoi(*argv);
        show_bytes((byte_pointer) &val, sizeof(unsigned));
        bits = set_high_byte_zero(val);
        show_bytes((byte_pointer) &bits, sizeof(unsigned));
        bits = set_high_byte_complement(val);
        show_bytes((byte_pointer) &bits, sizeof(unsigned));
        bits = set_last_byte_one(val);
        show_bytes((byte_pointer) &bits, sizeof(unsigned));
    }
    return 0;
}
