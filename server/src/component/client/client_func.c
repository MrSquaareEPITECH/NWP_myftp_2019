/*
** EPITECH PROJECT, 2020
** server
** File description:
** client_func.c
*/

#include "client_func.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "def/code.h"
#include "def/error.h"
#include "def/size.h"

int client_download(client_t *client, int dest)
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

int client_receive(client_t *client, char *buf, size_t count)
{
    if (read(client->con_control->fd, buf, count) == CODE_INVALID) {
        fprintf(stderr, "%s: %s", ERROR_CLIENT_RECEIVE, strerror(errno));
        return (CODE_ERROR);
    }
    return (CODE_SUCCESS);
}

int client_send(client_t *client, const char *buf, size_t count)
{
    if (write(client->con_control->fd, buf, count) == CODE_INVALID) {
        fprintf(stderr, "%s: %s", ERROR_CLIENT_SEND, strerror(errno));
        return (CODE_ERROR);
    }
    return (CODE_SUCCESS);
}

int client_upload(client_t *client, int src)
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