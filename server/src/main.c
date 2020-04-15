/*
** EPITECH PROJECT, 2020
** server
** File description:
** main.c
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "def/code.h"
#include "server.h"
#include "util/file.h"

int error(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Error: Missing arguments. Format: %s port path\n",
            argv[0]);

        return (CODE_ERROR);
    }

    char *endptr;

    strtol(argv[1], &endptr, 10);

    if (*endptr != '\0') {
        fprintf(stderr, "Error: Invalid port\n");

        return (CODE_ERROR);
    }

    if (dir_exists(argv[2]) == false) {
        fprintf(stderr, "Error: Invalid path: %s\n", strerror(errno));

        return (CODE_ERROR);
    }

    return (CODE_SUCCESS);
}

int main(int argc, char **argv)
{
    if (error(argc, argv))
        return (CODE_ERROR);

    server_t *server = server_create(argv[2], strtol(argv[1], NULL, 10));
    int code = 0;

    code = server->listen(server);
    code &= server->run(server);

    server_delete(server);

    return (code);
}