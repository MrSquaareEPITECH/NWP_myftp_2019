/*
** EPITECH PROJECT, 2020
** server
** File description:
** client.h
*/

#ifndef SERVER_SRC_CLIENT_H
#define SERVER_SRC_CLIENT_H

#include "socket.h"

typedef struct client_s client_t;

struct client_s {
    socket_t *control;
    socket_t *data;

    int (*download)(client_t *this, char *buf, size_t count);
    int (*receive)(client_t *this, char *buf, size_t count);
    int (*send)(client_t *this, const char *buf, size_t count);
    int (*upload)(client_t *this, const char *buf, size_t count);
};

client_t *client_create();
void client_delete(client_t *client);

#endif // SERVER_SRC_CLIENT_H
