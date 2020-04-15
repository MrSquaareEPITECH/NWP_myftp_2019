/*
** EPITECH PROJECT, 2020
** server
** File description:
** cdup.c
*/

#include "cdup.h"

#include "def/code.h"
#include "def/message.h"
#include "util/string.h"

static int cdup_validation(client_t *client, int argc, char **argv)
{
    (void)(argc);
    (void)(argv);

    if (client->state != STATE_LOGGED) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_LOGIN_MANDATORY));

        return (CODE_ERROR);
    }

    return (CODE_SUCCESS);
}

int cdup(server_t *server, client_t *client, int argc, char **argv)
{
    (void)(server);

    if (cdup_validation(client, argc, argv))
        return (CODE_ERROR);

    char *parent = string_find_r(client->directory, '/');

    if (parent != client->directory)
        *parent = '\0';

    client->messages->add(client->messages, string_format(MESSAGE_SUCCESS));

    return (CODE_SUCCESS);
}