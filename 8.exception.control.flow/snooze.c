#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>


unsigned int snooze(unsigned int secs) {
  unsigned int r = sleep(secs);
  printf("Slept for %u of %u secs.\n", secs-r, secs);
  return r;
}

void handler(int signum) {
  return;
}

int main(int argc, char *argv[]){
  if (argc != 2) {
    printf("Usage: %s seconds\n", argv[0]);
    return -1;
  }
  if (signal(SIGINT, handler) == SIG_ERR) {
    fprintf(stderr, "register SIGINT handler failed, %s\n", strerror(errno));
    return -2;
  }

  unsigned int secs;
  secs = (unsigned int) strtol(argv[1], NULL, 10);
  return snooze(secs);
}
