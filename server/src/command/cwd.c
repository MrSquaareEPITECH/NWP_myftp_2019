/*
** EPITECH PROJECT, 2020
** server
** File description:
** cwd.c
*/

#include "cwd.h"

#include "def/code.h"
#include "def/message.h"
#include "util/string.h"

static int cwd_validation(client_t *client, int argc, char **argv)
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

int cwd(server_t *server, client_t *client, int argc, char **argv)
{
    (void)(server);

    if (cwd_validation(client, argc, argv))
        return (CODE_ERROR);

    return (CODE_SUCCESS);
}