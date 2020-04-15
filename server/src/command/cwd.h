/*
** EPITECH PROJECT, 2020
** server
** File description:
** cwd.h
*/

#ifndef SERVER_SRC_COMMAND_CWD_H
#define SERVER_SRC_COMMAND_CWD_H

#include "client.h"
#include "server.h"

static const char *const HELP_CWD = "Change directory";

int cwd(server_t *server, client_t *client, int argc, char **argv);

#endif // SERVER_SRC_COMMAND_CWD_H
