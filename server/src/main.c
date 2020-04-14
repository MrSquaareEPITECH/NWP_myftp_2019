/*
** EPITECH PROJECT, 2020
** server
** File description:
** main.c
*/

#include <util/string.h>

#include "server.h"

int main()
{
    server_t* server = server_create(".", 20000);

    server->listen(server);
    server->run(server);

    server_delete(server);

    return (0);
}