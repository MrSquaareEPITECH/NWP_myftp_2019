/*
** EPITECH PROJECT, 2020
** server
** File description:
** socket_func.h
*/

#ifndef SERVER_SRC_COMPONENT_SOCKET_SOCKET_FUNC_H
#define SERVER_SRC_COMPONENT_SOCKET_SOCKET_FUNC_H

#include "socket.h"

int socket_accept(socket_t *this, socket_t *peer);
int socket_bind(socket_t *this, int type);
int socket_connect(socket_t *this, int type);
int socket_listen(socket_t *this, int max);

#endif // SERVER_SRC_COMPONENT_SOCKET_SOCKET_FUNC_H
