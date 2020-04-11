/*
** EPITECH PROJECT, 2020
** server
** File description:
** server.c
*/

#include "server.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "def/code.h"
#include "def/command.h"
#include "def/error.h"
#include "def/message.h"
#include "def/size.h"
#include "util/string.h"

static int server_accept(server_t* this)
{
    if (FD_ISSET(this->control->fd, &this->read_fd_set) == 0)
        return (CODE_SUCCESS);

    client_t* client = client_create();

    if (client->control->accept(client->control, this->control)) {
        fprintf(stderr, "%s: ", ERROR_SERVER_ACCEPT);

        return (CODE_ERROR);
    }

    if (client->send(client, MESSAGE_WELCOME, strlen(MESSAGE_WELCOME))) {
        fprintf(stderr, "%s: ", ERROR_SERVER_ACCEPT);

        return (CODE_ERROR);
    }

    if (this->clients->add(this->clients, client)) {
        fprintf(stderr, "%s: ", ERROR_SERVER_ACCEPT);

        return (CODE_ERROR);
    }

    FD_SET(client->control->fd, &this->active_fd_set);

    return (CODE_SUCCESS);
}

static int server_execute(server_t* this, client_t* client)
{
    if (FD_ISSET(client->control->fd, &this->read_fd_set) == 0)
        return (CODE_SUCCESS);

    char message[SIZE_MESSAGE];

    if (client->receive(client, message, SIZE_MESSAGE)) {
        fprintf(stderr, "%s: ", ERROR_SERVER_COMMAND);

        return (CODE_ERROR);
    }

    string_crlf(message);

    char** args = string_split(message, " ");

    for (size_t i = 0; COMMANDS[i].name; ++i) {
        if (strcasecmp(COMMANDS[i].name, args[0]) == 0) {
            if (COMMANDS[i].func(this, client, args)) {
                fprintf(stderr, "%s: ", ERROR_SERVER_COMMAND);

                return (CODE_ERROR);
            }
        }
    }

    return (CODE_SUCCESS);
}

static int server_listen(server_t* this)
{
    if (this->control->bind(this->control, SOCK_STREAM)) {
        fprintf(stderr, "%s: ", ERROR_SERVER_LISTEN);

        return (CODE_ERROR);
    }

    if (this->control->listen(this->control, 1)) {
        fprintf(stderr, "%s: ", ERROR_SERVER_LISTEN);

        return (CODE_ERROR);
    }

    return (CODE_SUCCESS);
}

static int server_run(server_t* this)
{
    FD_SET(this->control->fd, &this->active_fd_set);

    while (true) {
        this->read_fd_set = this->active_fd_set;
        this->write_fd_set = this->active_fd_set;

        if (select(FD_SETSIZE, &this->read_fd_set, &this->write_fd_set, NULL,
                NULL) == CODE_INVALID) {
            fprintf(stderr, "%s: %s\n", ERROR_SERVER_SELECT, strerror(errno));

            return (CODE_ERROR);
        }

        if (this->accept(this)) {
            return (CODE_ERROR);
        }

        for (client_chain_t* item = this->clients->begin; item;
             item = item->next)
            this->execute(this, item->client);
    }
}

server_t* server_create(const char* directory, uint16_t port)
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
    server->run = server_run;

    return server;
}

void server_delete(server_t* server)
{
    if (server == NULL)
        return;

    client_list_delete(server->clients);
    socket_delete(server->control);

    free(server);
}