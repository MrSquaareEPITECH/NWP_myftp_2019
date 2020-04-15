/*
** EPITECH PROJECT, 2020
** server
** File description:
** client.h
*/

#ifndef SERVER_SRC_CLIENT_H
#define SERVER_SRC_CLIENT_H

#include <stdbool.h>

#include "message_list.h"
#include "socket.h"

enum TRANSFER_MODE { TRANSFER_UNKNOWN, TRANSFER_ACTIVE, TRANSFER_PASSIVE };
enum STATE { STATE_UNKNOWN, STATE_CONNECTED, STATE_LOGGED, STATE_DISCONNECTED };

typedef struct client_s client_t;

struct client_s {
    socket_t *con_control;
    socket_t *con_data;
    socket_t *data;
    char *directory;
    char *user;
    message_list_t *messages;
    enum TRANSFER_MODE mode;
    enum STATE state;

    int (*download)(client_t *this, int dest);
    int (*receive)(client_t *this, char *buf, size_t count);
    int (*send)(client_t *this, const char *buf, size_t count);
    int (*upload)(client_t *this, int src);
};

client_t *client_create(void);
void client_delete(client_t *client);

#endif // SERVER_SRC_CLIENT_H
