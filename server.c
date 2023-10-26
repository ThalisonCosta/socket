#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  // char *message, server_reply[2048];

  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == -1) {
    puts("failed creat socket\n");
    exit(1);
  }

  struct sockaddr_in server, client;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(4444);
  server.sin_family = AF_INET;

  if (bind(sock_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
    puts("address already in use\n");
    exit(1);
  }
  puts("connected\n");

  listen(sock_fd, 5);

  int c = sizeof(struct sockaddr_in);
  int new_sock;

  while ((new_sock = accept(sock_fd, (struct sockaddr *)&client, (socklen_t *)&c)) > 0) {
    puts("connected succesfully");

    char *message = "message from server\n";

    write(new_sock, message, strlen(message));
  }
  return 0;
}
