#include "csapp.h"

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

void proxy(int fd);
void signale_handler(int signum);
void copy(int dst, int src, size_t chunksize);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);
void parse_url(char *url, char *hostname, char *port, char *uri);
void read_requesthdrs(rio_t *rp, char *buf);

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3";

void proxy(int fd)
{
    char req[MAXLINE];

    rio_t rio;
    Rio_readinitb(&rio, fd);

    if (!Rio_readlineb(&rio, req, MAXLINE))
      return;

    printf("%s", req);

    char method[MAXLINE], url[MAXLINE], version[MAXLINE];
    sscanf(req, "%s %s %s", method, url, version);
    printf("req: %s\n", req);

    char header[MAXLINE], resp[MAXLINE];
    /* read_requesthdrs(&rio, header); */
    /* printf("header:\n%s", header); */

    char hostname[MAXLINE], port[MAXLINE], uri[MAXLINE];
    int connfd;
    parse_url(url, hostname, port, uri);
    connfd = open_clientfd(hostname, port);

    if (connfd < 0) {
      printf("Failed connection to target host\n");
      sprintf(resp, "%s 404 FAILED\r\n", version);
    } else {
      printf("Connection established to target host\n");
      sprintf(resp, "%s 200 OK\r\n", version);
    }

    Rio_writen(fd, resp, strlen(resp));

    read_requesthdrs(&rio, header);

    printf("client --> server\n");
    sprintf(req, "GET %s %s\r\n", uri, version);
    printf("req:\n%s", req);
    Rio_writen(connfd, req, strlen(req));
    sprintf(header, "%s\r\n", header);
    printf("header:\n%s-------------\n", header);
    Rio_writen(connfd, header, strlen(header));

    printf("server --> client\n");
    copy(fd, connfd, 4096);
    Close(connfd);
}

void signale_handler(int signum) {

}

void copy(int dst, int src, size_t chunksize)
{
  char *buf = Malloc((chunksize+1)*sizeof(char));
  ssize_t count;
  do {
    count = Rio_readn(src, buf, chunksize);
    *(buf+count) = '\0';
    printf("read from src %d: %zd\n%s\n------------\n", src, count, buf);

    Rio_writen(dst, buf, count);
    printf("sended to dst %d\n", dst);
  } while (count == (ssize_t)chunksize);
}

void parse_url(char *url, char *hostname, char *port, char *uri)
{
  char *p;
  for (p = hostname; *p = *url, *p != ':' && *p != '/' && *p != '\0'; url++, p++)
    ;

  // only hostname
  if (*p == '\0') {
    // defaults to http
    strcpy(port, "80");
    return;
  }

  char scheme[MAXLINE];

  if (*p == ':' && *(url + 1) == '/' && *(url + 2) == '/') {
    // scheme
    *p = '\0';
    strcpy(scheme, hostname);
    url += 3;

    // hostname
    for (p = hostname; *p = *url, *p != ':' && *p != '/' && *p != '\0'; url++, p++)
      ;
  }

  if (*p == ':') {
    // ending hostname
    *p = '\0';
    // port
    for (p = port, ++url; *url != '/' && *url != '\0'; p++, url++) {
      *p = *url;
    }
    *p = '\0';
  } else {
    // ending hostname
    *p = '\0';

    // port is not specified
    if (strcmp(scheme, "https") == 0) {
      strcpy(port, "443");
    } else if (strcmp(scheme, "http") == 0) {
      strcpy(port, "80");
    } else {
      // unknown scheme
      strcpy(port, "");
    }
  }


  // uri
  if (*url == '\0') {
    strcpy(uri, "/");
    return;
  }

  for (p = uri; *p = *url, *p != '\0'; p++, url++)
    ;
}

void read_requesthdrs(rio_t *rp, char *header)
{
  int ret;
  char buf[MAXLINE];

  if ((ret=Rio_readlineb(rp, buf, MAXLINE)) < 0) {
    return;
  }
  while (strcmp(buf, "\r\n") != 0) {
    strcpy(header, buf);
    header += ret;
    ret = Rio_readlineb(rp, buf, MAXLINE);
  }
  return;
}

void clienterror(int fd, char *cause, char *errnum,
		 char *shortmsg, char *longmsg)
{
  char buf[MAXLINE], body[MAXBUF];
  /* Build the HTTP response body */
  sprintf(body, "<html><title>Tiny Error</title>");
  sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
  sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
  sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
  sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

  /* Print the HTTP response */
  sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "Content-type: text/html\r\n");
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
  Rio_writen(fd, buf, strlen(buf));
  Rio_writen(fd, body, strlen(body));
}
