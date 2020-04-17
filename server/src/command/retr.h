/*
** EPITECH PROJECT, 2020
** server
** File description:
** retr.h
*/

#ifndef SERVER_SRC_COMMAND_RETR_H
#define SERVER_SRC_COMMAND_RETR_H

#include "component/client/client.h"
#include "component/server/server.h"

static const char *const HELP_RETR = "Upload a file";

int retr(server_t *server, client_t *client, int argc, char **argv);

#endif // SERVER_SRC_COMMAND_RETR_H
