#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  char *host = "127.0.0.1";
  int port = 4444;

  int server_sock, client_sock;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_size;
  char buffer[1024];

  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock < 0) {
    perror("socket error");
    exit(1);
  }

  printf("socket server created.\n");

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(host);

  int fd =
      bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (fd < 0) {
    perror("bind error");
    exit(1);
  }

  printf("bind to port: %d\n", port);

  listen(server_sock, 5);

  while (1) {
    addr_size = sizeof(client_addr);
    client_sock =
        accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
    printf("client connected");

    bzero(buffer, 1024);
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("client: %s\n", buffer);

    bzero(buffer, 1024);
    strcpy(buffer, "message from server");
    printf("server: %s\n", buffer);
    send(client_sock, buffer, strlen(buffer), 0);

    close(client_sock);
    printf("client disconnected\n\n");
  }

  return 0;
}
