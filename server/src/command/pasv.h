/*
** EPITECH PROJECT, 2020
** server
** File description:
** pasv.h
*/

#ifndef SERVER_SRC_COMMAND_PASV_H
#define SERVER_SRC_COMMAND_PASV_H

#include "client.h"
#include "server.h"

static const char *const HELP_PASV = "Use passive mode";

int pasv(server_t *server, client_t *client, int argc, char **argv);

#endif // SERVER_SRC_COMMAND_PASV_H
