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

  struct sockaddr_in server, client;

  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(4444);
  server.sin_family = AF_INET;

  if (bind(sock_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
    printf("address already in use\n");
    exit(1);
  }
  printf("connected\n");

  listen(sock_fd, 5);

  int c = sizeof(struct sockaddr_in);
  int new_sock;

  while (1) {
    if ((new_sock = accept(sock_fd, (struct sockaddr *)&client,
                           (socklen_t *)&c)) > 0) {
      char message[100];
      memset(message, 0, sizeof(message));

      while (1) {
        if (read(new_sock, message, sizeof(message)) <= 0) {
          printf("Client disconnected");
          close(new_sock);
          break;
        }

        printf("client: %s\n", message);

        printf("server: ");
        fgets(message, sizeof(message), stdin);

        write(new_sock, message, strlen(message));
      }
    }
  }
  return 0;
}
