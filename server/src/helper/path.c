/*
** EPITECH PROJECT, 2020
** server
** File description:
** path.c
*/

#include "path.h"

#include "util/string.h"

char *path_find(server_t *server, client_t *client, char *sub)
{
    char *path = NULL;

    if (*sub == '/')
        path = string_format("%s/%s", server->directory, sub);
    else
        path = string_format(
            "%s/%s/%s", server->directory, client->directory, sub);

    return (path);
}