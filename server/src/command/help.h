/*
** EPITECH PROJECT, 2020
** server
** File description:
** help.h
*/

#ifndef SERVER_SRC_COMMAND_HELP_H
#define SERVER_SRC_COMMAND_HELP_H

#include "component/client/client.h"
#include "component/server/server.h"

static const char *const HELP_HELP = "Display help";

int help(server_t *server, client_t *client, int argc, char **argv);

#endif // SERVER_SRC_COMMAND_HELP_H
