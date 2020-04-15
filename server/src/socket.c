/*
** EPITECH PROJECT, 2020
** server
** File description:
** socket.c
*/

#include "socket.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "def/code.h"
#include "def/error.h"

static int socket_accept(socket_t *this, socket_t *peer)
{
    uint32_t size = sizeof(this->addr_in);

    this->fd = accept(peer->fd, (sockaddr_t *)(&this->addr_in), &size);
    if (this->fd == CODE_INVALID) {
        fprintf(stderr, "%s: %s\n", ERROR_SOCKET_ACCEPT, strerror(errno));
        return (CODE_ERROR);
    }
    return (CODE_SUCCESS);
}

static int socket_bind(socket_t *this, int type)
{
    this->fd = socket(this->addr_in.sin_family, type, 0);
    if (this->fd == CODE_INVALID) {
        fprintf(stderr, "%s: %s\n", ERROR_SOCKET_CREATE, strerror(errno));

        return (CODE_ERROR);
    }
    if (bind(this->fd, (sockaddr_t *)(&this->addr_in), sizeof(this->addr_in))) {
        fprintf(stderr, "%s: %s\n", ERROR_SOCKET_BIND, strerror(errno));
        return (CODE_ERROR);
    }
    return (CODE_SUCCESS);
}

static int socket_connect(socket_t *this, int type)
{
    this->fd = socket(this->addr_in.sin_family, type, 0);
    if (this->fd == CODE_INVALID) {
        fprintf(stderr, "%s: %s\n", ERROR_SOCKET_CREATE, strerror(errno));
        return (CODE_ERROR);
    }
    if (connect(this->fd, (sockaddr_t *)(&this->addr_in),
            sizeof(this->addr_in)) == -1) {
        fprintf(stderr, "%s: %s\n", ERROR_SOCKET_CONNECT, strerror(errno));
        return (CODE_ERROR);
    }
    return (CODE_SUCCESS);
}

static int socket_listen(socket_t *this, int max)
{
    if (listen(this->fd, max)) {
        fprintf(stderr, "%s: %s\n", ERROR_SOCKET_LISTEN, strerror(errno));
        return (CODE_ERROR);
    }
    return (CODE_SUCCESS);
}

socket_t *socket_create(uint32_t addr, uint32_t family)
{
    return socket_create_p(addr, family, 0);
}

socket_t *socket_create_p(uint32_t addr, uint32_t family, uint16_t port)
{
    socket_t *socket = malloc(sizeof(socket_t));

    if (socket == NULL)
        return (NULL);
    socket->addr_in.sin_addr.s_addr = addr;
    socket->addr_in.sin_family = family;
    socket->addr_in.sin_port = htons(port);
    socket->accept = socket_accept;
    socket->bind = socket_bind;
    socket->connect = socket_connect;
    socket->listen = socket_listen;
    return socket;
}

void socket_delete(socket_t *socket)
{
    if (socket == NULL)
        return;
    close(socket->fd);
    free(socket);
}