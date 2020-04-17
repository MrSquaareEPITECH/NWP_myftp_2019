/*
** EPITECH PROJECT, 2020
** server
** File description:
** client.c
*/

#include "client.h"

#include <stdlib.h>

#include "client_func.h"

client_t *client_create(void)
{
    client_t *client = malloc(sizeof(client_t));

    if (client == NULL)
        return (NULL);

    client->con_control = socket_create(INADDR_ANY, PF_INET);
    client->con_data = NULL;
    client->data = NULL;
    client->directory = NULL;
    client->user = NULL;
    client->messages = message_list_create();
    client->mode = TRANSFER_UNKNOWN;
    client->state = STATE_UNKNOWN;
    client->download = client_download;
    client->receive = client_receive;
    client->send = client_send;
    client->upload = client_upload;
    return client;
}

void client_delete(client_t *client)
{
    if (client == NULL)
        return;

    socket_delete(client->con_control);
    socket_delete(client->con_data);
    socket_delete(client->data);
    message_list_delete(client->messages);
    free(client->directory);
    free(client->user);
    free(client);
}
