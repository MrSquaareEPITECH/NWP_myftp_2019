/*
** EPITECH PROJECT, 2020
** server
** File description:
** server_func.c
*/

#include "server_func.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "component/client/client.h"
#include "def/code.h"
#include "def/error.h"
#include "server_client.h"

int server_accept(server_t* this)
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
    if (server_client_add(this, client))
        return (CODE_ERROR);
    return (CODE_SUCCESS);
}

int server_execute(server_t* this)
{
    for (client_chain_t* item = this->clients->begin; item; item = item->next) {
        if (item->client->state == STATE_DISCONNECTED) {
            if (server_client_remove(this, item->client))
                return (CODE_ERROR);
            return (CODE_SUCCESS);
        }
        if (FD_ISSET(item->client->con_control->fd, &this->read_fd_set))
            if (server_client_call_command(this, item->client))
                return (CODE_ERROR);
        if (FD_ISSET(item->client->con_control->fd, &this->write_fd_set))
            if (server_client_send_message(this, item->client))
                return (CODE_ERROR);
    }
    return (CODE_SUCCESS);
}

int server_listen(server_t* this)
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

int server_select(server_t* this)
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

int server_run(server_t* this)
{
    FD_SET(this->control->fd, &this->active_fd_set);
    while (true) {
        if (this->select(this))
            return (CODE_ERROR);
        if (this->accept(this))
            return (CODE_ERROR);
        if (this->execute(this)) {
            fprintf(stderr, "Can't execute\n");
            return (CODE_ERROR);
        }
    }
}