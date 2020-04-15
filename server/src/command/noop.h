/*
** EPITECH PROJECT, 2020
** server
** File description:
** noop.h
*/

#ifndef SERVER_SRC_COMMAND_NOOP_H
#define SERVER_SRC_COMMAND_NOOP_H

#include "client.h"
#include "server.h"

static const char *const HELP_NOOP = "Noop noop!!!";

int noop(server_t *server, client_t *client, int argc, char **argv);

#endif // SERVER_SRC_COMMAND_NOOP_H
