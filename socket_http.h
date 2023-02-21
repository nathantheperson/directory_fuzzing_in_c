#pragma once 

#include "config.h"

int createSockHttp();

int connectSockHttp(int socket_call, char* host, in_port_t port);
 
int sendHttp(int socket_call, char* built_request);

int recvHttp(int socket_call, char* server_reply);
