/*
** EPITECH PROJECT, 2020
** server
** File description:
** retr.c
*/

#include "retr.h"

#include <stdlib.h>

#include "def/code.h"
#include "def/message.h"
#include "helper/path.h"
#include "retr_fork.h"
#include "util/path.h"
#include "util/string.h"

static int retr_validation_path(server_t *server, client_t *client, char *file)
{
    char *path = path_find(server, client, file);

    if (file_exists(path) == false) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_FILE_UNAVAILABLE));
        return (CODE_ERROR);
    }
    free(path);
    return (CODE_SUCCESS);
}

static int retr_validation(
    server_t *server, client_t *client, int argc, char **argv)
{
    if (client->state != STATE_LOGGED) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_LOGIN_MANDATORY));
        return (CODE_ERROR);
    }
    if (client->mode == TRANSFER_UNKNOWN) {
        client->messages->add(
            client->messages, string_format(MESSAGE_UNKNOWN_MODE));
        return (CODE_ERROR);
    }
    if (argc < 2) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_ARGUMENTS));
        return (CODE_ERROR);
    }
    if (retr_validation_path(server, client, argv[1]))
        return (CODE_ERROR);
    return (CODE_SUCCESS);
}

int retr(server_t *server, client_t *client, int argc, char **argv)
{
    if (retr_validation(server, client, argc, argv))
        return (CODE_ERROR);

    char *path = path_find(server, client, argv[1]);

    if (retr_fork(client, path))
        return (CODE_ERROR);
    free(path);
    return (CODE_SUCCESS);
}
