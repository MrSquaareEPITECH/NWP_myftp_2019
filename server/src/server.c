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
#include "helper/command.h"
#include "util/args.h"
#include "util/string.h"

static int server_client_add(server_t* this, client_t* client)
{
    if (this->clients->add(this->clients, client))
        return (CODE_ERROR);

    FD_SET(client->con_control->fd, &this->active_fd_set);

    if (client->send(client, MESSAGE_WELCOME, strlen(MESSAGE_WELCOME)))
        return (CODE_ERROR);

    return (CODE_SUCCESS);
}

static int server_client_read(server_t* this, client_t* client)
{
    if (FD_ISSET(client->con_control->fd, &this->read_fd_set) == 0)
        return (CODE_SUCCESS);

    char message[SIZE_MESSAGE];

    memset(message, 0, SIZE_MESSAGE);

    if (client->receive(client, message, SIZE_MESSAGE))
        return (CODE_ERROR);

    string_brk(message);

    char** argv = args_create(message, " ");
    int argc = args_count(argv);

    if (argc < 1)
        return (CODE_ERROR); // TODO: Better error

    const command_t* command = command_find(argv[0]);

    if (command == NULL) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_UNKNOWN));

        return (CODE_ERROR); // TODO: Better error
    }

    return (command->func(this, client, argc, argv));
}

static int server_client_write(server_t* this, client_t* client)
{
    (void)(this);

    for (message_chain_t* item = client->messages->begin; item;
         item = item->next) {
        if (FD_ISSET(client->con_control->fd, &this->write_fd_set) == 0)
            return (CODE_SUCCESS);

        if (client->send(client, item->message, strlen(item->message)))
            return (CODE_ERROR);

        if (client->messages->remove(client->messages, item->message))
            return (CODE_ERROR);
    }

    return (CODE_SUCCESS);
}

static int server_client_remove(server_t* this, client_t* client)
{
    if (client->send(client, MESSAGE_QUIT, strlen(MESSAGE_QUIT)))
        return (CODE_ERROR);

    if (this->clients->remove(this->clients, client))
        return (CODE_ERROR);

    FD_CLR(client->con_control->fd, &this->active_fd_set);

    client_delete(client);

    return (CODE_SUCCESS);
}

static int server_accept(server_t* this)
{
    if (FD_ISSET(this->control->fd, &this->read_fd_set) == 0)
        return (CODE_SUCCESS);

    client_t* client = client_create();

    if (client->con_control->accept(client->con_control, this->control)) {
        fprintf(stderr, "%s: ", ERROR_SERVER_ACCEPT);

        return (CODE_ERROR);
    }

    client->directory = strdup("/");
    client->state = STATE_CONNECTED;

    this->client_add(this, client);

    return (CODE_SUCCESS);
}

static int server_execute(server_t* this)
{
    for (client_chain_t* item = this->clients->begin; item; item = item->next) {
        if (item->client->state == STATE_DISCONNECTED) {
            this->client_remove(this, item->client);

            return (CODE_SUCCESS);
        }

        server_client_read(this, item->client);
        server_client_write(this, item->client);
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

static int server_select(server_t* this)
{
    this->read_fd_set = this->active_fd_set;
    this->write_fd_set = this->active_fd_set;

    if (select(FD_SETSIZE, &this->read_fd_set, &this->write_fd_set, NULL,
            NULL) == CODE_INVALID) {
        fprintf(stderr, "%s: %s\n", ERROR_SERVER_SELECT, strerror(errno));

        return (CODE_ERROR);
    }

    return (CODE_SUCCESS);
}

static int server_run(server_t* this)
{
    FD_SET(this->control->fd, &this->active_fd_set);

    while (true) {
        if (this->select(this))
            return (CODE_ERROR);

        if (this->accept(this))
            return (CODE_ERROR);

        if (this->execute(this))
            return (CODE_ERROR);
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
    server->client_add = server_client_add;
    server->client_remove = server_client_remove;
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

    if (server->control)
        socket_delete(server->control);

    if (server->clients)
        client_list_delete(server->clients);

    free(server);
}