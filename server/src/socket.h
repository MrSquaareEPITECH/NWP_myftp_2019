/*
** EPITECH PROJECT, 2020
** server
** File description:
** socket.h
*/

#ifndef SERVER_SRC_SOCKET_H
#define SERVER_SRC_SOCKET_H

#include <netinet/in.h>
#include <stdint.h>

typedef struct sockaddr sockaddr_t;
typedef struct sockaddr_in sockaddr_in_t;
typedef struct socket_s socket_t;

struct socket_s {
    sockaddr_in_t addr_in;
    int fd;

    int (*accept)(socket_t *this, socket_t *peer);
    int (*bind)(socket_t *this, int type);
    int (*connect)(socket_t *this, int type);
    int (*listen)(socket_t *this, int max);
};

socket_t *socket_create(uint32_t addr, uint32_t family);
socket_t *socket_create_p(uint32_t addr, uint32_t family, uint16_t port);
void socket_delete(socket_t* socket);

#endif // SERVER_SRC_SOCKET_H
