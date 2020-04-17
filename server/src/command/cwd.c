/*
** EPITECH PROJECT, 2020
** server
** File description:
** cwd.c
*/

#include "cwd.h"

#include <stdlib.h>
#include <string.h>

#include "def/code.h"
#include "def/message.h"
#include "helper/path.h"
#include "util/path.h"
#include "util/string.h"

static int cwd_validation_path(server_t *server, client_t *client, char *dir)
{
    char *path = path_find(server, client, dir);

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

static char *cwd_directory(server_t *server, client_t *client, char *dir)
{
    char *relative = path_find(server, client, dir);
    char *real = path_real(relative);
    char *directory = NULL;

    if (strstr(real, server->directory))
        directory = strdup(&real[strlen(server->directory)]);
    else
        directory = strdup("/");
    free(relative);
    free(real);
    return (directory);
}

int cwd(server_t *server, client_t *client, int argc, char **argv)
{
    if (cwd_validation(server, client, argc, argv))
        return (CODE_ERROR);

    char *directory = cwd_directory(server, client, argv[1]);

    free(client->directory);
    client->directory = directory;
    client->messages->add(client->messages, string_format(MESSAGE_FILE_OK));
    return (CODE_SUCCESS);
}