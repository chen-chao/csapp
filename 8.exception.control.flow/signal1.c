#include "../csapp.h"

void handler2(int sig) {
  pid_t pid;

  while ((pid = waitpid(-1, NULL, 0)) > 0) {
    printf("Handler reaped child %d\n", (int)pid);
  }

  if (errno != ECHILD)
    unix_error("waitpid error");

  Sleep(2);
  return;
}

int main() {
  int i, n;
  char buf[MAXBUF];

  if (signal(SIGCHLD, handler2) == SIG_ERR)
    unix_error("signal error");

  /* Parent creates children */
  for (i = 0; i < 3; i++) {
    if (Fork() == 0) {
      printf("Hello from child %d\n", (int)getpid());
      Sleep(1);
      exit(0);
    }
  }

  /* Parent waits for terminal input and then process it */
  /* Linux would restart slow syscalls automatically, but some old
     systems would stop and set errno to EINTR. So we should manually
     restart read for portability. */

  /* this is workable on Linux, or using sigaction to register signal handler:
     if ((n = read(STDOUT_FILENO, buf, sizeof(buf))) < 0)
       unix_error("read error");
  */

  /* this is for portability */
  while ((n = read(STDOUT_FILENO, buf, sizeof(buf))) < 0)
    if (errno != EINTR)
      unix_error("read error");

  printf("Parent processing input\n");
  while (1)
    ;

  exit(0);
}
