/*
** EPITECH PROJECT, 2020
** server
** File description:
** list.c
*/

#include "list.h"

#include <stdlib.h>

#include "def/code.h"
#include "def/message.h"
#include "helper/path.h"
#include "list_fork.h"
#include "util/path.h"
#include "util/string.h"

static int list_validation_path(server_t *server, client_t *client, char *dir)
{
    char *path = path_find(server, client, dir);

    if (dir_exists(path) == false) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_FILE_UNAVAILABLE));
        return (CODE_ERROR);
    }
    free(path);
    return (CODE_SUCCESS);
}

static int list_validation(
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
    if (argc == 2)
        if (list_validation_path(server, client, argv[1]))
            return (CODE_ERROR);
    return (CODE_SUCCESS);
}

int list(server_t *server, client_t *client, int argc, char **argv)
{
    (void)(server);

    if (list_validation(server, client, argc, argv))
        return (CODE_ERROR);

    char *path = NULL;

    if (argc == 2)
        path = path_find(server, client, argv[1]);
    else
        path = string_format("%s/%s", server->directory, client->directory);

    if (list_fork(client, path))
        return (CODE_ERROR);
    return (CODE_SUCCESS);
}