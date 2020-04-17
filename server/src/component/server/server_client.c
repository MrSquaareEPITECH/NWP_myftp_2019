/*
** EPITECH PROJECT, 2020
** server
** File description:
** server_client.c
*/

#include "server_client.h"

#include <stdlib.h>
#include <string.h>

#include "component/client/client.h"
#include "def/code.h"
#include "def/command.h"
#include "def/message.h"
#include "def/size.h"
#include "helper/command.h"
#include "util/args.h"
#include "util/string.h"

static int server_client_receive_command(
    client_t* client, int* argc, char*** argv)
{
    char message[SIZE_MESSAGE];

    memset(message, 0, SIZE_MESSAGE);
    if (client->receive(client, message, SIZE_MESSAGE))
        return (CODE_ERROR);
    string_brk(message);
    *argv = args_create(message, " ");
    *argc = args_count(*argv);
    return (CODE_SUCCESS);
}

int server_client_add(server_t* this, client_t* client)
{
    if (this->clients->add(this->clients, client))
        return (CODE_ERROR);
    FD_SET(client->con_control->fd, &this->active_fd_set);
    if (client->send(client, MESSAGE_WELCOME, strlen(MESSAGE_WELCOME)))
        return (CODE_ERROR);
    return (CODE_SUCCESS);
}

int server_client_call_command(server_t* this, client_t* client)
{
    int argc = 0;
    char** argv = NULL;

    if (server_client_receive_command(client, &argc, &argv))
        return (CODE_ERROR);
    if (argc < 1)
        return (CODE_SUCCESS);
    if (command_find(argv[0]) == NULL) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_UNKNOWN));
        return (CODE_SUCCESS);
    }

    const command_t* command = command_find(argv[0]);

    command->func(this, client, argc, argv);
    return (CODE_SUCCESS);
}

int server_client_send_message(server_t* this, client_t* client)
{
    (void)(this);

    for (message_chain_t* item = client->messages->begin; item;) {
        if (FD_ISSET(client->con_control->fd, &this->write_fd_set) == 0)
            return (CODE_SUCCESS);
        if (client->send(client, item->message, strlen(item->message)))
            return (CODE_ERROR);
        message_chain_t* current = item;
        item = item->next;
        if (client->messages->remove(client->messages, current->message))
            return (CODE_ERROR);
        free(current->message);
        free(current);
    }
    return (CODE_SUCCESS);
}

int server_client_remove(server_t* this, client_t* client)
{
    if (client->send(client, MESSAGE_QUIT, strlen(MESSAGE_QUIT)))
        return (CODE_ERROR);
    if (this->clients->remove(this->clients, client))
        return (CODE_ERROR);
    FD_CLR(client->con_control->fd, &this->active_fd_set);
    client_delete(client);
    return (CODE_SUCCESS);
}