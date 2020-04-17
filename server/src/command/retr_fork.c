/*
** EPITECH PROJECT, 2020
** server
** File description:
** retr_fork.c
*/

#include "retr_fork.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "def/code.h"
#include "def/message.h"

static int retr_connect(client_t *client)
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

static int retr_upload(client_t *client, const char *path)
{
    int file = open(path, O_RDONLY);

    if (file == CODE_INVALID) {
        fprintf(stderr, "Can't open: %s\n", strerror(errno));
        return (CODE_ERROR);
    }
    if (client->upload(client, file))
        return (CODE_ERROR);
    close(file);
    return (CODE_SUCCESS);
}

static int retr_disconnect(client_t *client)
{
    socket_delete(client->con_data);

    if (client->mode == TRANSFER_PASSIVE)
        socket_delete(client->data);
    client->con_data = NULL;
    client->data = NULL;
    client->mode = TRANSFER_UNKNOWN;
    return (CODE_SUCCESS);
}

int retr_fork(client_t *client, const char *path)
{
    int pid = fork();

    if (pid == 0) {
        client->send(
            client, MESSAGE_CONNECTION_OPEN, strlen(MESSAGE_CONNECTION_OPEN));
        if (retr_connect(client))
            return (CODE_ERROR);
        if (retr_upload(client, path))
            return (CODE_ERROR);
        if (retr_disconnect(client))
            return (CODE_ERROR);
        client->send(
            client, MESSAGE_CONNECTION_CLOSE, strlen(MESSAGE_CONNECTION_CLOSE));
    }
    return (CODE_SUCCESS);
}