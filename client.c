#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == -1) {
    puts("failed creat socket\n");
    exit(1);
  }

  struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_port = htons(4444);
  server.sin_family = AF_INET;

  if (connect(sock_fd, (struct sockaddr *)&server, sizeof(server)) <0 ) {
    puts("failed to connect\n");
    exit(1);
  }
  puts("connected");

  char *message = "GET / HTTP/1.1\r\n\r\n";

  if (send(sock_fd, message, strlen(message), 0) < 0) {
    puts("failed send message\n");
    exit(1);
  }
  puts("data sent\n");

  char server_reply[2048];
  if (recv(sock_fd, server_reply, 2048, 0) < 0) {
    puts("failed to receive message\n");
    exit(1);
  }

  puts("received data\n");
  puts(server_reply);

  return 0;
}
