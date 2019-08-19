\#include <stdio.h>
#include "../csapp.h"

void doit() {
  Fork();
  Fork();
  printf("hello\n");
}

int main() {
  doit();
  printf("hello\n");
  exit(0);
}
