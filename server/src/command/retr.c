/*
** EPITECH PROJECT, 2020
** server
** File description:
** retr.c
*/

#include "retr.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "def/code.h"
#include "def/message.h"

int retr(server_t *server, client_t *client, char **args)
{
    (void) args;

    if (!FD_ISSET(client->con_control->fd, &server->write_fd_set))
        return (CODE_SUCCESS);

    if (client->send(client, MESSAGE_RETR_OPEN, strlen(MESSAGE_RETR_OPEN)))
        return (CODE_ERROR);

    if (client->mode == TRANSFER_ACTIVE) {
        if (client->con_data->connect(client->con_data, SOCK_STREAM))
            return (CODE_ERROR);
    } else if (client->mode == TRANSFER_PASSIVE) {
        client->con_data = socket_create(0, 0);

        if (client->con_data->accept(client->con_data, client->data))
            return (CODE_ERROR);
    }

    int file = open(args[1], O_RDONLY);

    if (file == CODE_INVALID) {
        fprintf(stderr, "Can't open: %s\n", strerror(errno));

        return (CODE_ERROR);
    }

    if (client->upload(client, file))
        return (CODE_ERROR);

    close(file);
    socket_delete(client->con_data);

    if (client->mode == TRANSFER_PASSIVE)
        socket_delete(client->data);

    client->con_data = NULL;
    client->data = NULL;
    client->mode = TRANSFER_UNKNOWN;

    if (client->send(client, MESSAGE_RETR_CLOSE, strlen(MESSAGE_RETR_CLOSE)))
        return (CODE_ERROR);

    return (CODE_SUCCESS);
}
