/*
** EPITECH PROJECT, 2020
** server
** File description:
** stor.c
*/

#include "stor.h"

#include <stdlib.h>

#include "def/code.h"
#include "def/message.h"
#include "stor_fork.h"
#include "util/string.h"

static int stor_validation(client_t *client, int argc, char **argv)
{
    (void)(argv);

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
    return (CODE_SUCCESS);
}

int stor(server_t *server, client_t *client, int argc, char **argv)
{
    if (stor_validation(client, argc, argv))
        return (CODE_ERROR);

    char *path = string_format(
        "%s/%s/%s", server->directory, client->directory, argv[1]);

    if (stor_fork(client, path))
        return (CODE_ERROR);
    free(path);
    return (CODE_SUCCESS);
}
