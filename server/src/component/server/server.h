/*
** EPITECH PROJECT, 2020
** server
** File description:
** server.h
*/

#ifndef SERVER_SRC_SERVER_H
#define SERVER_SRC_SERVER_H

#include <stdbool.h>
#include <stdint.h>

#include "client_list.h"
#include "component/socket/socket.h"

typedef struct server_s server_t;

struct server_s {
    client_list_t *clients;
    socket_t *control;
    socket_t *data;
    char *directory;

    fd_set active_fd_set;
    fd_set read_fd_set;
    fd_set write_fd_set;

    int (*accept)(server_t *this);
    int (*execute)(server_t *this);
    int (*listen)(server_t *this);
    int (*select)(server_t *this);
    int (*run)(server_t *this);
};

server_t *server_create(char *directory, uint16_t port);
void server_delete(server_t *server);

#endif // SERVER_SRC_SERVER_H
