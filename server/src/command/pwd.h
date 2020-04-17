/*
** EPITECH PROJECT, 2020
** server
** File description:
** pwd.h
*/

#ifndef SERVER_SRC_COMMAND_PWD_H
#define SERVER_SRC_COMMAND_PWD_H

#include "component/client/client.h"
#include "component/server/server.h"

static const char *const HELP_PWD = "Print directory";

int pwd(server_t *server, client_t *client, int argc, char **argv);

#endif // SERVER_SRC_COMMAND_PWD_H
