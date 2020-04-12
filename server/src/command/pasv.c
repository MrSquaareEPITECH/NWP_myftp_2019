/*
** EPITECH PROJECT, 2020
** server
** File description:
** pasv.c
*/

#include "pasv.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "def/code.h"
#include "def/message.h"

static char *pasv_information(client_t *client)
{
    char *address = inet_ntoa(client->data->addr_in.sin_addr);
    int port = 30000;

    int len = snprintf(NULL, 0, "%s,%d,%d", address, port / 256, port % 256);
    char *information = malloc(sizeof(char) * (len + 1));

    sprintf(information, "%s,%d,%d", address, port / 256, port % 256);

    for (int i = 0; i < len; ++i)
        if (information[i] == '.')
            information[i] = ',';

    return (information);
}

static char *pasv_message(client_t *client)
{
    char *information = pasv_information(client);
    size_t len = strlen(MESSAGE_PASV) + strlen(information);
    char *message = malloc(sizeof(char) * (len + 1));

    sprintf(message, MESSAGE_PASV, information);

    free(information);

    return (message);
}

int pasv(server_t *server, client_t *client, char **args)
{
    (void)args;

    if (!FD_ISSET(client->con_control->fd, &server->write_fd_set))
        return (CODE_SUCCESS);

    client->data = socket_create_p(INADDR_ANY, PF_INET, 30000);

    if (client->data->bind(client->data, SOCK_STREAM))
        return (CODE_ERROR);

    if (client->data->listen(client->data, 1))
        return (CODE_ERROR);

    client->mode = TRANSFER_PASSIVE;

    char *message = pasv_message(client);

    if (client->send(client, message, strlen(message)))
        return (CODE_ERROR);

    free(message);

    return (CODE_SUCCESS);
}