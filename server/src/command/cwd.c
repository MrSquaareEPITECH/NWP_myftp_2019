/*
** EPITECH PROJECT, 2020
** server
** File description:
** cwd.c
*/

#include "cwd.h"

#include <stdlib.h>

#include "def/code.h"
#include "def/message.h"
#include "util/file.h"
#include "util/string.h"

static int cwd_validation_path(server_t *server, client_t *client, char *sub)
{
    char *path = string_format(
        "%s/%s/%s", server->directory, client->directory, sub);

    if (dir_exists(path) == false) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_FILE_UNAVAILABLE));
        return (CODE_ERROR);
    }
    free(path);
    return (CODE_SUCCESS);
}

static int cwd_validation(
    server_t *server, client_t *client, int argc, char **argv)
{
    (void)(argv);

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
    if (cwd_validation_path(server, client, argv[1]))
        return (CODE_ERROR);
    return (CODE_SUCCESS);
}

int cwd(server_t *server, client_t *client, int argc, char **argv)
{
    if (cwd_validation(server, client, argc, argv))
        return (CODE_ERROR);

    char *directory = string_format("%s/%s", client->directory, argv[1]);

    free(client->directory);
    client->directory = directory;
    client->messages->add(client->messages, string_format(MESSAGE_FILE_OK));
    return (CODE_SUCCESS);
}