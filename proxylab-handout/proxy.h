#ifndef PROXY_H__
#define PROXY_H__

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

void proxy(int fd);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);
void parse_url(char *url, char *hostname, char *port);
void read_requesthdrs(rio_t *rp, char *buf);

#endif
