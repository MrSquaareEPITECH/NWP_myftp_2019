/*
** EPITECH PROJECT, 2020
** server
** File description:
** command.h
*/

#ifndef SERVER_SRC_TYPE_COMMAND_H
#define SERVER_SRC_TYPE_COMMAND_H

#include "component/client/client.h"
#include "component/server/server.h"

typedef struct command_s command_t;

struct command_s {
    const char *name;
    const char *help;
    int (*func)(server_t *server, client_t *client, int argc, char **argv);
};

#endif // SERVER_SRC_TYPE_COMMAND_H
