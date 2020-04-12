/*
** EPITECH PROJECT, 2020
** server
** File description:
** quit.c
*/

#include "quit.h"

#include <string.h>

#include "def/code.h"
#include "def/message.h"

int quit(server_t *server, client_t *client, char **args)
{
    (void) args;

    if (!FD_ISSET(client->con_control->fd, &server->write_fd_set))
        return (CODE_SUCCESS);

    if (client->send(client, MESSAGE_QUIT, strlen(MESSAGE_QUIT)))
        return (CODE_ERROR);

    FD_CLR(client->con_control->fd, &server->active_fd_set);

    if (server->clients->remove(server->clients, client))
        return (CODE_ERROR);

    client_delete(client);

    return (CODE_SUCCESS);
}