#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


/* 10.8
 *
 * unix> fstatcheck 3 < foo.txt
 *
 * will raise "Bad file descriptor error", so shell closed before executing commands:
 *
 * if (Fork() == 0) {
 *     dup2(0, 3) ? redirect 3 to stdin
 *     Execve("fstatcheck", argv, envp);
 * }
 */


void unix_error(char *msg) {
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(0);
}

int Fstat(int fd, struct stat *buf) {
  int ret;
  if ((ret = fstat(fd, buf)) != 0) {
    unix_error("fstat error");
  }
  return 0;
}

int main(int argc, char *argv[]) {
  struct stat status;
  char *type, *readok;
  int fd;

  if (argc != 2) {
    printf("Usage: statcheck fd\n");
    return -1;
  }

  char *rem;
  fd = (int) strtol(argv[1], &rem, 10);
  if (*rem != '\0') {
    printf("invalid input: %s", rem);
    return -1;
  }

  Fstat(fd, &status);

  if (S_ISREG(status.st_mode)) {
    type = "regular";
  } else if (S_ISDIR(status.st_mode)) {
    type = "directory";
  } else {
    type = "other";
  }

  if ((status.st_mode & S_IRUSR)) {
    readok = "yes";
  } else {
    readok = "no";
  }

  printf("type: %s, read: %s\n", type, readok);

  return 0;
}
