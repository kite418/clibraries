#include "ksock.h"

/*
    TODO
    ERROR CHECKING
*/

SockServer* make_server(char * address, int port) {
    // CREATE SERVER SOCKET
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // DEFINE SERVER ADDRESS
    struct sockaddr_in* server_addr = malloc(sizeof(struct sockaddr_in));
    server_addr->sin_family = AF_INET;
    server_addr->sin_port = htons(port);
    server_addr->sin_addr.s_addr = inet_addr(address);

    // BIND SOCKET
    bind(server_socket, (struct sockaddr*) server_addr, sizeof(*server_addr));

    // BUILD SOCKSERVER*
    SockServer* sock_server = malloc(sizeof(sock_server));
    sock_server->server_addr = server_addr;
    sock_server->port = port;
    sock_server->server_socket = server_socket;

    return sock_server;
}

int sock_server_send(SockClient* target_client, char buffer[], size_t buffer_size) {
    int bytes_sent = send(target_client->client_socket, buffer, buffer_size, 0);
    return bytes_sent;
}

void sock_server_close(SockServer* sock_server) {
    close(sock_server->server_socket);
}

// EXPECTS NULL TERMINATED MESSAGE BUFFER
void sock_server_message(SockClient* target_client, char message[]) {
    sock_server_send(target_client, message, strlen(message));
}

void sock_server_listen(SockServer* sock_server, int max_clients) {
    listen(sock_server->server_socket, max_clients);
    printf("Server started listening on port %i\n", sock_server->port);
}

int sock_server_recv(SockClient* target_client, char buffer[], size_t data_length) {
    return recv(target_client->client_socket, buffer, data_length, 0);
}

SockClient* sock_server_accept(SockServer* sock_server) {
    SockClient* sock_client = malloc(sizeof(SockClient));
    int client_socket = accept(sock_server->server_socket, NULL, NULL);
    sock_client->client_socket = client_socket;
    return sock_client;
}

SockClient* make_client(char* address, int port) {
    // CREATE CLIENT SOCKET
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // DEFINE REMOTE SERVER ADDRS
    struct sockaddr_in* server_addr = malloc(sizeof(struct sockaddr_in));
    server_addr->sin_family = AF_INET;
    server_addr->sin_port = htons(port);
    server_addr->sin_addr.s_addr =  inet_addr(address);

    SockClient* client = malloc(sizeof(SockClient));
    client->server_addr = server_addr;
    client->client_socket = client_socket;

    return client;
}

int sock_client_dial(SockClient* client) {
    struct sockaddr_in* addr = client->server_addr;
    int connection_status = connect(client->client_socket, (struct sockaddr*) client->server_addr, sizeof(*addr));
    return connection_status;
}

int sock_client_recv(SockClient* client, char buffer[], size_t data_length) {
    return recv(client->client_socket, buffer, data_length, 0);
}

void sock_client_close(SockClient* client) {
    close(client->client_socket);
}

