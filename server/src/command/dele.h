/*
** EPITECH PROJECT, 2020
** server
** File description:
** dele.h
*/

#ifndef SERVER_SRC_COMMAND_DELE_H
#define SERVER_SRC_COMMAND_DELE_H

#include "component/client/client.h"
#include "component/server/server.h"

static const char *const HELP_DELE = "Delete a file";

int dele(server_t *server, client_t *client, int argc, char **argv);

#endif // SERVER_SRC_COMMAND_DELE_H
