/*
** EPITECH PROJECT, 2020
** server
** File description:
** port.c
*/

#include "port.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "def/code.h"
#include "def/message.h"
#include "util/string.h"

void port_information(const char *information, uint32_t *addr, uint16_t *port)
{
    char **split = string_split(information, ",");

    int len = snprintf(
        NULL, 0, "%s.%s.%s.%s", split[0], split[1], split[2], split[3]);

    char *address = malloc(sizeof(char) * (len + 1));

    memset(address, 0, len + 1);
    sprintf(address, "%s.%s.%s.%s", split[0], split[1], split[2], split[3]);

    *addr = inet_addr(address);
    *port = (atoi(split[4]) * 256) + atoi(split[5]);
}

int port(server_t *server, client_t *client, char **args)
{
    (void)args;

    if (!FD_ISSET(client->con_control->fd, &server->write_fd_set))
        return (CODE_SUCCESS);

    uint32_t addr = 0;
    uint16_t port = 0;

    port_information(args[1], &addr, &port);

    client->con_data = socket_create_p(addr, PF_INET, port);
    client->mode = TRANSFER_ACTIVE;

    if (client->send(client, MESSAGE_SUCCESS, strlen(MESSAGE_SUCCESS)))
        return (CODE_ERROR);

    return (CODE_SUCCESS);
}