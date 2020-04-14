/*
** EPITECH PROJECT, 2020
** server
** File description:
** port.h
*/

#ifndef SERVER_SRC_COMMAND_PORT_H
#define SERVER_SRC_COMMAND_PORT_H

#include "client.h"
#include "server.h"

static const char *const HELP_PORT = "Use active mode";

int port(server_t *server, client_t *client, int argc, char **argv);

#endif // SERVER_SRC_COMMAND_PORT_H
