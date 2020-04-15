/*
** EPITECH PROJECT, 2020
** server
** File description:
** user.c
*/

#include "user.h"

#include <string.h>

#include "def/code.h"
#include "def/message.h"
#include "util/string.h"

static int user_validation(client_t *client, int argc, char **argv)
{
    (void)(client);
    (void)(argv);

    if (client->state == STATE_LOGGED) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_LOGIN_GUEST));

        return (CODE_ERROR);
    }

    if (argc < 2) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_LOGIN_MANDATORY));

        return (CODE_ERROR);
    }

    return (CODE_SUCCESS);
}

char *user_message()
{
    char *message = string_format(MESSAGE_PASSWORD);

    return (message);
}

int user(server_t *server, client_t *client, int argc, char **argv)
{
    (void)(server);

    if (user_validation(client, argc, argv))
        return (CODE_ERROR);

    client->user = strdup(argv[1]);

    client->messages->add(client->messages, user_message());

    return (CODE_SUCCESS);
}