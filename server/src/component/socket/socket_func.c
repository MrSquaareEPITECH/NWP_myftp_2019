/*
** EPITECH PROJECT, 2020
** server
** File description:
** socket_func.c
*/

#include "socket_func.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "def/code.h"
#include "def/error.h"

int socket_accept(socket_t *this, socket_t *peer)
{
    uint32_t size = sizeof(this->addr_in);

    this->fd = accept(peer->fd, (sockaddr_t *)(&this->addr_in), &size);
    if (this->fd == CODE_INVALID) {
        fprintf(stderr, "%s: %s\n", ERROR_SOCKET_ACCEPT, strerror(errno));
        return (CODE_ERROR);
    }
    return (CODE_SUCCESS);
}

int socket_bind(socket_t *this, int type)
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

int socket_connect(socket_t *this, int type)
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

int socket_listen(socket_t *this, int max)
{
    if (listen(this->fd, max)) {
        fprintf(stderr, "%s: %s\n", ERROR_SOCKET_LISTEN, strerror(errno));
        return (CODE_ERROR);
    }
    return (CODE_SUCCESS);
}