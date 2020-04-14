/*
** EPITECH PROJECT, 2020
** server
** File description:
** user.h
*/

#ifndef SERVER_SRC_COMMAND_USER_H
#define SERVER_SRC_COMMAND_USER_H

#include "client.h"
#include "server.h"

static const char *const HELP_USER = "Specify user";

int user(server_t *server, client_t *client, int argc, char **argv);

#endif // SERVER_SRC_COMMAND_USER_H
