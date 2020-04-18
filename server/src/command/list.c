/*
** EPITECH PROJECT, 2020
** server
** File description:
** list.c
*/

#include "list.h"

#include "def/code.h"
#include "def/message.h"
#include "list_fork.h"
#include "util/string.h"

static int list_validation(client_t *client, int argc, char **argv)
{
    (void)(argc);
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
    return (CODE_SUCCESS);
}

int list(server_t *server, client_t *client, int argc, char **argv)
{
    (void)(server);

    if (list_validation(client, argc, argv))
        return (CODE_ERROR);

    char *path = string_format("%s/%s", server->directory, client->directory);

    if (list_fork(client, path))
        return (CODE_ERROR);
    return (CODE_SUCCESS);
}