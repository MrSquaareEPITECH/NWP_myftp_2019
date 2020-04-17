/*
** EPITECH PROJECT, 2020
** server
** File description:
** list.c
*/

#include "list.h"

#include <unistd.h>

#include "def/code.h"
#include "def/message.h"
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
    return (CODE_SUCCESS);
}

int list_fork(server_t *server, client_t *client)
{
    int pid = fork();

    char *path = string_format("%s/%s", server->directory, client->directory);

    if (pid == 0) {
        dup2(client->con_control->fd, 1);

        execl("/bin/ls", "ls", "-la", path, NULL);
    }

    return (CODE_SUCCESS);
}

int list(server_t *server, client_t *client, int argc, char **argv)
{
    (void)(server);

    if (list_validation(client, argc, argv))
        return (CODE_ERROR);
    if (list_fork(server, client))
        return (CODE_ERROR);
    return (CODE_SUCCESS);
}