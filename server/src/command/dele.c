/*
** EPITECH PROJECT, 2020
** server
** File description:
** dele.c
*/

#include "dele.h"

#include <stdio.h>
#include <stdlib.h>

#include "def/code.h"
#include "def/message.h"
#include "util/file.h"
#include "util/string.h"

static int dele_validation_path(server_t *server, client_t *client, char *sub)
{
    char *path = string_format(
        "%s/%s/%s", server->directory, client->directory, sub);

    if (file_exists(path) == false) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_FILE_UNAVAILABLE));
        return (CODE_ERROR);
    }
    free(path);
    return (CODE_SUCCESS);
}

static int dele_validation(
    server_t *server, client_t *client, int argc, char **argv)
{
    if (client->state != STATE_LOGGED) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_LOGIN_MANDATORY));
        return (CODE_ERROR);
    }
    if (argc < 2) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_ARGUMENTS));
        return (CODE_ERROR);
    }
    if (dele_validation_path(server, client, argv[1]))
        return (CODE_ERROR);
    return (CODE_SUCCESS);
}

int dele(server_t *server, client_t *client, int argc, char **argv)
{
    if (dele_validation(server, client, argc, argv))
        return (CODE_ERROR);

    char *path = string_format(
        "%s/%s/%s", server->directory, client->directory, argv[1]);

    if (remove(path) == CODE_INVALID)
        return (CODE_ERROR);
    client->messages->add(client->messages, string_format(MESSAGE_FILE_OK));
    return (CODE_SUCCESS);
}