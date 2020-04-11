/*
** EPITECH PROJECT, 2020
** server
** File description:
** client.c
*/

#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "def/code.h"
#include "def/error.h"

static int client_download(client_t *client, char *buf, size_t count)
{
    if (read(client->data->fd, buf, count) == CODE_INVALID) {
        fprintf(stderr, "%s: ", ERROR_CLIENT_DOWNLOAD);

        return (CODE_ERROR);
    }

    return (CODE_SUCCESS);
}

static int client_receive(client_t *client, char *buf, size_t count)
{
    if (read(client->control->fd, buf, count) == CODE_INVALID) {
        fprintf(stderr, "%s: ", ERROR_CLIENT_RECEIVE);

        return (CODE_ERROR);
    }

    return (CODE_SUCCESS);
}

static int client_send(client_t *client, const char *buf, size_t count)
{
    if (write(client->control->fd, buf, count) == CODE_INVALID) {
        fprintf(stderr, "%s: ", ERROR_CLIENT_SEND);

        return (CODE_ERROR);
    }

    return (CODE_SUCCESS);
}

static int client_upload(client_t *client, const char *buf, size_t count)
{
    if (write(client->data->fd, buf, count) == CODE_INVALID) {
        fprintf(stderr, "%s: ", ERROR_CLIENT_UPLOAD);

        return (CODE_ERROR);
    }

    return (CODE_SUCCESS);
}

client_t *client_create()
{
    client_t *client = malloc(sizeof(client_t));

    if (client == NULL)
        return (NULL);

    client->control = socket_create(INADDR_ANY, PF_INET);
    client->data = NULL;

    client->download = client_download;
    client->receive = client_receive;
    client->send = client_send;
    client->upload = client_upload;

    return client;
}

void client_delete(client_t *client)
{
    if (client == NULL)
        return;

    if (client->control)
        socket_delete(client->control);

    if (client->data)
        socket_delete(client->data);

    free(client);
}
