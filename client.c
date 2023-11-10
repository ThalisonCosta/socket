#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct {
  char *http_method;
  char *path;
  char *host;
} Args;

Args parseCommandLineArgs(int argc, char *argv[]) {
  Args args = {NULL, NULL, NULL};

  if (argc != 3) {
    printf("Usage: %s <HTTP_METHOD> <URL>\n", argv[0]);
    exit(1);
  }

  args.http_method = argv[1];
  char *url = argv[2];

  char *url_start = strstr(url, "http://");
  if (url_start == NULL) {
    printf("Invalid URL format. Use 'http://'.\n");
    exit(1);
  }

  url_start += 7;
  args.host = url_start;

  char *path_start = strchr(url_start, '/');
  *path_start = '\0';
  path_start++;
  args.path = path_start;

  return args;
}

int main(int argc, char **argv) {
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == -1) {
    printf("Failed to create socket\n");
    exit(1);
  }

  Args args = parseCommandLineArgs(argc, argv);

  int port;
  char *port_str = strchr(args.host, ':');
  if (port_str) {
    *port_str = '\0';
    port_str++;
    port = atoi(port_str);
  }

  struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_port = htons(port);
  server.sin_family = AF_INET;

  if (connect(sock_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
    printf("Failed to connect\n");
    exit(1);
  }

  const char *request_string = "%s /%s HTTP/1.1\r\n"
                               "Host: %s\r\n"
                               "\r\n";

  int request_length = snprintf(NULL, 0, request_string, args.http_method,
                                args.path, args.host) +
                       1;

  char *http_request = (char *)malloc(request_length);

  snprintf(http_request, request_length, request_string, args.http_method,
           args.path, args.host);

  send(sock_fd, http_request, strlen(http_request), 0);

  free(http_request);

  char server_reply[4048];
  if (recv(sock_fd, server_reply, 2048, 0) < 0) {
    printf("Failed to receive message\n");
    exit(1);
  }
  printf("Response: %s\n", server_reply);

  close(sock_fd);
  return 0;
}
