/*
** EPITECH PROJECT, 2020
** server
** File description:
** stor_fork.c
*/

#include "stor_fork.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "def/code.h"
#include "def/message.h"

static int stor_connect(client_t *client)
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

static int stor_download(client_t *client, const char *path)
{
    int file = open(path, O_WRONLY | O_CREAT);

    if (file == CODE_INVALID) {
        fprintf(stderr, "Can't open: %s\n", strerror(errno));
        return (CODE_ERROR);
    }
    if (client->download(client, file))
        return (CODE_ERROR);
    close(file);
    return (CODE_SUCCESS);
}

static int stor_disconnect(client_t *client)
{
    socket_delete(client->con_data);

    if (client->mode == TRANSFER_PASSIVE)
        socket_delete(client->data);
    client->con_data = NULL;
    client->data = NULL;
    client->mode = TRANSFER_UNKNOWN;
    return (CODE_SUCCESS);
}

int stor_fork(client_t *client, const char *path)
{
    int pid = fork();

    if (pid == 0) {
        client->send(
            client, MESSAGE_CONNECTION_OPEN, strlen(MESSAGE_CONNECTION_OPEN));
        if (stor_connect(client))
            return (CODE_ERROR);
        if (stor_download(client, path))
            return (CODE_ERROR);
        if (stor_disconnect(client))
            return (CODE_ERROR);
        client->send(
            client, MESSAGE_CONNECTION_CLOSE, strlen(MESSAGE_CONNECTION_CLOSE));
    }
    return (CODE_SUCCESS);
}
