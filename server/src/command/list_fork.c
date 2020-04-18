/*
** EPITECH PROJECT, 2020
** server
** File description:
** list_fork.c
*/

#include "list_fork.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "def/code.h"
#include "def/message.h"

static int list_connect(client_t *client)
{
    if (client->mode == TRANSFER_ACTIVE) {
        if (client->con_data->connect(client->con_data, SOCK_STREAM))
            return (CODE_ERROR);
    } else if (client->mode == TRANSFER_PASSIVE) {
        client->con_data = socket_create(0, 0);
        if (client->con_data->accept(client->con_data, client->data))
            return (CODE_ERROR);
    }
    return (CODE_SUCCESS);
}

static int list_display(client_t *client, const char *path)
{
    dup2(client->con_data->fd, 1);
    if (execl("/bin/ls", "ls", "-la", path, NULL) == -1)
        return (CODE_ERROR);
    return (CODE_SUCCESS);
}

static int list_disconnect(client_t *client)
{
    socket_delete(client->con_data);

    if (client->mode == TRANSFER_PASSIVE)
        socket_delete(client->data);
    client->con_data = NULL;
    client->data = NULL;
    client->mode = TRANSFER_UNKNOWN;
    return (CODE_SUCCESS);
}

int list_fork(client_t *client, const char *path)
{
    int pid = fork();

    if (pid == 0) {
        client->send(
            client, MESSAGE_CONNECTION_OPEN, strlen(MESSAGE_CONNECTION_OPEN));
        if (list_connect(client))
            return (CODE_ERROR);
        if (list_display(client, path))
            return (CODE_ERROR);
        if (list_disconnect(client))
            return (CODE_ERROR);
        client->send(
            client, MESSAGE_CONNECTION_CLOSE, strlen(MESSAGE_CONNECTION_CLOSE));
    }
    return (CODE_SUCCESS);
}
