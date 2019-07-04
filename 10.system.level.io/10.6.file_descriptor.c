#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
  int fd1, fd2;
  fd1 = open("./data/foo.txt", O_RDONLY, 0);
  fd2 = open("./data/bar.txt", O_RDONLY, 0);
  close(fd2);
  fd2 = open("./data/baz.txt", O_RDONLY, 0);
  printf("fd2 = %d\n", fd2);
  return 0;
}
