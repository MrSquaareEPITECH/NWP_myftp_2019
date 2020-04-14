/*
** EPITECH PROJECT, 2020
** server
** File description:
** client.c
*/

#include "client.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "def/code.h"
#include "def/error.h"
#include "def/size.h"

static int client_download(client_t *client, int dest)
{
    char buf[SIZE_MESSAGE];
    int nbytes = 0;

    do {
        memset(buf, 0, SIZE_MESSAGE);

        nbytes = read(client->con_data->fd, buf, SIZE_MESSAGE);

        if (nbytes == CODE_INVALID) {
            fprintf(stderr, "%s: %s", ERROR_CLIENT_DOWNLOAD, strerror(errno));

            return (CODE_ERROR);
        }

        if (write(dest, buf, nbytes) == CODE_INVALID) {
            fprintf(stderr, "%s: %s", ERROR_CLIENT_DOWNLOAD, strerror(errno));

            return (CODE_ERROR);
        }
    } while (nbytes > 0);

    return (CODE_SUCCESS);
}

static int client_receive(client_t *client, char *buf, size_t count)
{
    if (read(client->con_control->fd, buf, count) == CODE_INVALID) {
        fprintf(stderr, "%s: %s", ERROR_CLIENT_RECEIVE, strerror(errno));

        return (CODE_ERROR);
    }

    return (CODE_SUCCESS);
}

static int client_send(client_t *client, const char *buf, size_t count)
{
    if (write(client->con_control->fd, buf, count) == CODE_INVALID) {
        fprintf(stderr, "%s: %s", ERROR_CLIENT_SEND, strerror(errno));

        return (CODE_ERROR);
    }

    return (CODE_SUCCESS);
}

static int client_upload(client_t *client, int src)
{
    char buf[SIZE_MESSAGE];
    int nbytes = 0;

    do {
        memset(buf, 0, SIZE_MESSAGE);

        nbytes = read(src, buf, SIZE_MESSAGE);

        if (nbytes == CODE_INVALID) {
            fprintf(stderr, "%s: %s", ERROR_CLIENT_UPLOAD, strerror(errno));

            return (CODE_ERROR);
        }

        if (write(client->con_data->fd, buf, nbytes) == CODE_INVALID) {
            fprintf(stderr, "%s: %s", ERROR_CLIENT_UPLOAD, strerror(errno));

            return (CODE_ERROR);
        }
    } while (nbytes > 0);

    return (CODE_SUCCESS);
}

client_t *client_create()
{
    client_t *client = malloc(sizeof(client_t));

    if (client == NULL)
        return (NULL);

    client->con_control = socket_create(INADDR_ANY, PF_INET);
    client->con_data = NULL;
    client->data = NULL;
    client->directory = NULL;
    client->user = NULL;
    client->messages = message_list_create();
    client->mode = TRANSFER_UNKNOWN;
    client->state = STATE_UNKNOWN;

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

    socket_delete(client->con_control);
    socket_delete(client->con_data);
    socket_delete(client->data);

    message_list_delete(client->messages);

    free(client->directory);
    free(client->user);

    free(client);
}
