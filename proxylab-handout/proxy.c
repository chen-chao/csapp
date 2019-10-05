#include "csapp.h"
#include "proxy.h"

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";


int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  int listenfd = Open_listenfd(argv[1]);

  int connfd;
  struct sockaddr_storage clientaddr;
  socklen_t clientlen;
  char hostname[MAXLINE], port[MAXLINE];

  while (1) {
    clientlen = sizeof(clientaddr);
    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    Getnameinfo((SA *)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
    printf("Accepted connection from %s\n", hostname);
    proxy(connfd);
    Close(connfd);
  }

  return 0;
}

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

    /* TODO: support other method */
    if (strcmp(method, "GET") != 0) {
      clienterror(fd, method, "501", "Not implemented", "proxy does not implement this method");
    }

    char hostname[MAXLINE], args[MAXLINE], port[MAXLINE];
    parse_url(url, hostname, port);

    char header[MAXLINE];
    read_requesthdrs(&rio, header);

    int connfd;
    if ((connfd = open_clientfd(hostname, port)) < 0) {
      clienterror(fd, method, "500", "Failed Connection", "Cannot connect to target host");
    }
    Rio_writen(connfd, req, strlen(req));
    Rio_writen(connfd, header, strlen(header));

    /* read from connfd, write to fd */
    off_t sendlen;

    if (sendfile(connfd, fd, 0, &sendlen, NULL, 0) != 0) {
      unix_error("sendfile failed");
    }
}

void parse_url(char *url, char *hostname, char *port)
{
  char buf[MAXLINE];
  char *p;
  for (p = buf; *url != ':' && *url != '\0'; url++, p++) {
    *p = *url;
  }

  // only hostname
  if (*url == '\0') {
    *p = '\0';
    strcpy(hostname, p);
    strcpy(port, "80");
    return;
  }

  // scheme
  if (*++url == '/') {
    if (*++url != '/') {
      unix_error("invalid scheme");
    }
  }

  // hostname
  for (p = buf; *url != ':' && *url != '/' && *url != '\0'; url++, p++) {
    *p = *url;
  }
  *p = '\0';
  strcpy(hostname, p);

  // port
  if (*url == ':') {
    for (p = port, ++url; *url != '/' && *url != '\0'; url++) {
      *p = *url;
    }
    *p = '\0';
    strcpy(port, p);
  } else {
    strcpy(port, "80");
  }
}

void read_requesthdrs(rio_t *rp, char *header)
{
  int ret;
  char buf[MAXLINE];

  if ((ret=Rio_readlineb(rp, buf, MAXLINE)) < 0) {
    return;
  }
  printf("%s", buf);
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
