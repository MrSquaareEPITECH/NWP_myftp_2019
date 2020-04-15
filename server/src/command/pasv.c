/*
** EPITECH PROJECT, 2020
** server
** File description:
** pasv.c
*/

#include "pasv.h"

#include <arpa/inet.h>
#include <string.h>

#include "def/code.h"
#include "def/message.h"
#include "util/string.h"

static int pasv_validation(client_t *client, int argc, char **argv)
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

static char *pasv_information(client_t *client)
{
    uint32_t size = sizeof(client->data->addr_in);

    getsockname(
        client->data->fd, (sockaddr_t *)(&client->data->addr_in), &size);

    char *address = inet_ntoa(client->data->addr_in.sin_addr);
    int port = ntohs(client->data->addr_in.sin_port);

    char *information =
        string_format("%s,%d,%d", address, port / 256, port % 256);

    for (size_t i = 0, len = strlen(information); i < len; ++i)
        if (information[i] == '.')
            information[i] = ',';

    return (information);
}

static char *pasv_message(client_t *client)
{
    char *information = pasv_information(client);
    char *message = string_format(MESSAGE_PASV, information);

    return (message);
}

int pasv(server_t *server, client_t *client, int argc, char **argv)
{
    (void)(server);

    if (pasv_validation(client, argc, argv))
        return (CODE_ERROR);
    client->data = socket_create(INADDR_ANY, PF_INET);
    client->mode = TRANSFER_PASSIVE;
    if (client->data->bind(client->data, SOCK_STREAM))
        return (CODE_ERROR);
    if (client->data->listen(client->data, 1))
        return (CODE_ERROR);
    client->messages->add(client->messages, pasv_message(client));
    return (CODE_SUCCESS);
}