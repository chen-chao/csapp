#include <unistd.h>
#include <stdio.h>

extern char **environ;

int main(int argc, char *argv[]){
    int i;

    printf("Comand line arguments:\n");
    for (i = 0; argv[i] != NULL; i++)
      printf("\targv[%2d]: %s\n", i, argv[i]);

    printf("\n");

    printf("Environment variables:\n");
    for (i = 0; environ[i] != NULL; i++)
      printf("\tenvp[%2d]: %s\n", i, environ[i]);

    return 0;
}
