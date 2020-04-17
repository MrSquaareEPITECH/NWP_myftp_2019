/*
** EPITECH PROJECT, 2020
** server
** File description:
** server.c
*/

#include "server.h"

#include <stdlib.h>
#include <string.h>

#include "component/client/client.h"
#include "server_func.h"

server_t* server_create(char* directory, uint16_t port)
{
    server_t* server = malloc(sizeof(server_t));

    if (server == NULL)
        return (NULL);
    server->clients = client_list_create();
    server->control = socket_create_p(INADDR_ANY, PF_INET, port);
    server->directory = directory;
    FD_ZERO(&server->active_fd_set);
    FD_ZERO(&server->read_fd_set);
    FD_ZERO(&server->write_fd_set);
    server->accept = server_accept;
    server->execute = server_execute;
    server->listen = server_listen;
    server->select = server_select;
    server->run = server_run;
    return server;
}

void server_delete(server_t* server)
{
    if (server == NULL)
        return;
    if (server->directory)
        free(server->directory);
    if (server->control)
        socket_delete(server->control);
    if (server->clients)
        client_list_delete(server->clients);
    free(server);
}