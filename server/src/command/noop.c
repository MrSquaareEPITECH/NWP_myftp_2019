/*
** EPITECH PROJECT, 2020
** server
** File description:
** noop.c
*/

#include "noop.h"

#include "def/code.h"
#include "def/message.h"
#include "util/string.h"

static int noop_validation(client_t *client, int argc, char **argv)
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

int noop(server_t *server, client_t *client, int argc, char **argv)
{
    (void)(server);

    if (noop_validation(client, argc, argv))
        return (CODE_ERROR);

    client->messages->add(client->messages, string_format(MESSAGE_SUCCESS));

    return (CODE_SUCCESS);
}