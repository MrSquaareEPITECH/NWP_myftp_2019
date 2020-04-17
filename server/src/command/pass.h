/*
** EPITECH PROJECT, 2020
** server
** File description:
** pass.h
*/

#ifndef SERVER_SRC_COMMAND_PASS_H
#define SERVER_SRC_COMMAND_PASS_H

#include "component/client/client.h"
#include "component/server/server.h"

static const char *const HELP_PASS = "Specify password";

int pass(server_t *server, client_t *client, int argc, char **argv);

#endif // SERVER_SRC_COMMAND_PASS_H
