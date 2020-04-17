/*
** EPITECH PROJECT, 2020
** server
** File description:
** cdup.h
*/

#ifndef SERVER_SRC_COMMAND_CDUP_H
#define SERVER_SRC_COMMAND_CDUP_H

#include "component/client/client.h"
#include "component/server/server.h"

static const char *const HELP_CDUP = "Change directory to parent directory";

int cdup(server_t *server, client_t *client, int argc, char **argv);

#endif // SERVER_SRC_COMMAND_CDUP_H
