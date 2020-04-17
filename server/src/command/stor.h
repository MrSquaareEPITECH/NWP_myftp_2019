/*
** EPITECH PROJECT, 2020
** server
** File description:
** stor.h
*/

#ifndef SERVER_SRC_COMMAND_STOR_H
#define SERVER_SRC_COMMAND_STOR_H

#include "component/client/client.h"
#include "component/server/server.h"

static const char *const HELP_STOR = "Download a file";

int stor(server_t *server, client_t *client, int argc, char **argv);

#endif // SERVER_SRC_COMMAND_STOR_H
