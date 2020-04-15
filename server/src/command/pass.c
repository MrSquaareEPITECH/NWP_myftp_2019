/*
** EPITECH PROJECT, 2020
** server
** File description:
** pass.c
*/

#include "pass.h"

#include <stdlib.h>
#include <string.h>

#include "def/code.h"
#include "def/message.h"
#include "util/string.h"

static int pass_validation(client_t *client, int argc, char **argv)
{
    (void)(argc);
    (void)(argv);

    if (client->user == NULL) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_LOGIN_USER));

        return (CODE_ERROR);
    }

    if (strcasecmp(client->user, "Anonymous") != 0) {
        free(client->user);

        client->user = NULL;

        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_LOGIN));

        return (CODE_ERROR);
    }

    return (CODE_SUCCESS);
}

char *pass_message()
{
    char *message = string_format(MESSAGE_LOGIN);

    return (message);
}

int pass(server_t *server, client_t *client, int argc, char **argv)
{
    (void)(server);

    if (pass_validation(client, argc, argv))
        return (CODE_ERROR);

    client->state = STATE_LOGGED;

    client->messages->add(client->messages, pass_message());

    return (CODE_SUCCESS);
}
