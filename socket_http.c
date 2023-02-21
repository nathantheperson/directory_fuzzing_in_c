#include "config.h"

int createSockHttp() {
  int socket_call;
  socket_call = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_call == -1) {
    printf("\n\nsocket_create() failed\n\n");
  }

  return socket_call;
}

int connectSockHttp(int socket_call, char* host, in_port_t port) {
  int sock_connect = 1;
  struct sockaddr_in server;

  server.sin_addr.s_addr = inet_addr(host);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  if (sock_connect =
          connect(socket_call, (struct sockaddr*)&server, sizeof(server)) < 0) {
    puts("\n\nconnect error\n\n");
    return 1;
  }

  return sock_connect;
}

int sendHttp(int socket_call, char* built_request) {

  if (send(socket_call, built_request, strlen(built_request), 0) < 0) {
    puts("\n\nsend failed\n\n");
    return 1;
  }

  return 0;
}

int recvHttp(int socket_call, char* server_reply) {

  int r = recv(socket_call, server_reply, MAX_LINE, 0);

  return r;
}
