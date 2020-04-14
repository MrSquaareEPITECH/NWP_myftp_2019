/*
** EPITECH PROJECT, 2020
** server
** File description:
** pwd.c
*/

#include "pwd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "def/code.h"
#include "def/message.h"
#include "util/string.h"

static int pwd_validation(client_t *client, int argc, char **argv)
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

static char *pwd_message(client_t *client)
{
    char *message = string_format(MESSAGE_PWD, client->directory);

    return message;
}

int pwd(server_t *server, client_t *client, int argc, char **argv)
{
    (void)(server);

    if (pwd_validation(client, argc, argv))
        return (CODE_ERROR);

    client->messages->add(client->messages, pwd_message(client));

    return (CODE_SUCCESS);
}