#include <stdio.h>
#include <stdlib.h>

int d2hex(char *d, char *hex) {
  char *rem;
  int val = (int) strtol(d, &rem, 10);
  if (*rem != '\0') {
    printf("invalid input %s", rem);
    return -1;
  }
  if (val > 255 || val < 0) {
    printf("invalid input %d", val);
    return -1;
  }
  return sprintf(hex, "%02x", val);
}

int dd2hex(char *dd, char *hex) {
  char temp[4];
  temp[3] = '\0';

  hex[0] = '0';
  hex[1] = 'x';
  hex += 2;

  int count = 0;
  int i = 0;
  int n;
  for (; *dd != '\0'; dd++) {
    if (i > 3) {
      printf("dd2hex: invalid %s", temp);
      return -1;
    }
    if (*dd == '.') {
      temp[i] = '\0';

      if ((n = d2hex(temp, hex)) < 0) {
	return -1;
      } else {
	hex += n;
      }
      i = 0;
      count++;
    } else {
      temp[i++] = *dd;
    }
  }
  if (i == 0) {
    printf("dd2hex: invalid termination");
    return -1;
  }
  if (count != 3) {
    printf("dd2hex: invalid length, got %d", count);
    return -1;
  }
  temp[i] = '\0';
  if ((n = d2hex(temp, hex)) < 0) {
    return -1;
  }
  *(hex+n) = '\0';
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: dd2hex ip\n");
    return -1;
  }

  char hex[11];
  int ret;
  if ((ret = dd2hex(argv[1], hex)) != 0) {
    return ret;
  }
  printf("%s\n", hex);
  return 0;
}
