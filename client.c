#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == -1) {
    printf("failed to create socket\n");
    exit(1);
  }

  struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_port = htons(4444);
  server.sin_family = AF_INET;

  if (connect(sock_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
    printf("failed to connect\n");
    exit(1);
  }

  const char *http_request = "GET / HTTP/1.1\r\n"
                             "Host: localhost\r\n"
                             "\r\n";
  send(sock_fd, http_request, strlen(http_request), 0);

  char server_reply[2048];
  if (recv(sock_fd, server_reply, 2048, 0) < 0) {
    printf("failed to receive message\n");
    exit(1);
  }
  printf("Response: %s\n", server_reply);

  close(sock_fd);
  return 0;
}
