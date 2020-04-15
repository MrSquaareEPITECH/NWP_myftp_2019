/*
** EPITECH PROJECT, 2020
** server
** File description:
** list.h
*/

#ifndef SERVER_SRC_COMMAND_LIST_H
#define SERVER_SRC_COMMAND_LIST_H

#include "client.h"
#include "server.h"

static const char *const HELP_LIST = "List files";

int list(server_t *server, client_t *client, int argc, char **argv);

#endif // SERVER_SRC_COMMAND_LIST_H
