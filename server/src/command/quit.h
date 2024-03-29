/*
** EPITECH PROJECT, 2020
** server
** File description:
** quit.h
*/

#ifndef SERVER_SRC_COMMAND_QUIT_H
#define SERVER_SRC_COMMAND_QUIT_H

#include "component/client/client.h"
#include "component/server/server.h"

static const char *const HELP_QUIT = "Disconnect";

int quit(server_t *server, client_t *client, int argc, char **argv);

#endif // SERVER_SRC_COMMAND_QUIT_H
