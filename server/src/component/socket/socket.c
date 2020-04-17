/*
** EPITECH PROJECT, 2020
** server
** File description:
** socket.c
*/

#include "socket.h"

#include <stdlib.h>
#include <unistd.h>

#include "socket_func.h"

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