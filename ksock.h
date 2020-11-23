#ifndef KSOCK_H
#define KSOCK_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stdio.h>

typedef struct s_server {
    struct sockaddr_in* server_addr;
    int port;
    int server_socket;
} SockServer;

typedef struct s_client {
    struct sockaddr_in* server_addr;
    int client_socket;
} SockClient;

SockServer* make_server(char * address, int port);
void sock_server_listen(SockServer* sock_server, int max_clients);
SockClient* sock_server_accept(SockServer* sock_server);
SockClient* make_client(char* address, int port);
int sock_client_dial(SockClient* client);
int sock_client_recv(SockClient* client, char buffer[], size_t data_length);
void sock_server_message(SockClient* target_client, char message[]);
int sock_server_send(SockClient* target_client, char buffer[], size_t buffer_size);
void sock_client_close(SockClient* client);
void sock_server_close(SockServer* sock_server);
int sock_server_recv(SockClient* target_client, char buffer[], size_t data_length);

#endif