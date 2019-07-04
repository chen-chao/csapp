#include <stdio.h>
#include <stdlib.h>

int hex2dd(char *s, char *result) {
  if (s[0] == '0' && s[1] == 'x')
    s += 2;

  char num[3];
  num[2] = '\0';
  int i, val;
  char temp[4];
  char *rem;
  
  for (i=0; i<4 && (num[0]=*s++) != '\0'; i++) {
    if ((num[1] = *s++) == '\0') {
      break;
    }
    val = (int) strtol(num, &rem, 16);
    if (*rem != '\0') {
      printf("hex2dd: invalid %s", rem);
      return -1;
    }
    if (sprintf(temp, "%d", val) < 0) {
      printf("hex2dd: error occurs.");
      return -1;
    }
    for (int j = 0; temp[j] != '\0'; j++, result++) {
      *result = temp[j];
    }
    *result++ = '.';
  }

  if (i != 4) {
    printf("hex2dd: invalid arguments number: %d", i);
    return -1;
  } else {
    *--result = '\0';
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: hex2dd hex\n");
    return -1;
  }

  char *result = malloc(sizeof(char)*16);
  int ret;
  
  if ((ret = hex2dd(argv[1], result)) != 0) {
    return ret;
  }
  printf("%s\n", result);
  return 0;
}
