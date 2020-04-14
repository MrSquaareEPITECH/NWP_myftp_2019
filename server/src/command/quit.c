/*
** EPITECH PROJECT, 2020
** server
** File description:
** quit.c
*/

#include "quit.h"

#include "def/code.h"

static int quit_validation(client_t *client, int argc, char **argv)
{
    (void)(client);
    (void)(argc);
    (void)(argv);

    return (CODE_SUCCESS);
}

int quit(server_t *server, client_t *client, int argc, char **argv)
{
    (void)(server);

    if (quit_validation(client, argc, argv))
        return (CODE_ERROR);

    client->state = STATE_DISCONNECTED;

    return (CODE_SUCCESS);
}