/*
** EPITECH PROJECT, 2020
** server
** File description:
** command.h
*/

#ifndef SERVER_SRC_TYPE_COMMAND_H
#define SERVER_SRC_TYPE_COMMAND_H

#include "client.h"
#include "server.h"

typedef struct command_s command_t;

struct command_s {
    const char *name;
    int (*func)(server_t *server, client_t *client, char **args);
};

#endif // SERVER_SRC_TYPE_COMMAND_H
