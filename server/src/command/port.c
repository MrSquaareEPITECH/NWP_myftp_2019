/*
** EPITECH PROJECT, 2020
** server
** File description:
** port.c
*/

#include "port.h"

#include <arpa/inet.h>
#include <stdlib.h>

#include "def/code.h"
#include "def/message.h"
#include "util/args.h"
#include "util/string.h"

static int port_validation(client_t *client, int argc, char **argv)
{
    if (client->state != STATE_LOGGED) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_LOGIN_MANDATORY));

        return (CODE_ERROR);
    }

    if (argc < 2) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_ARGUMENTS));

        return (CODE_ERROR);
    }

    if (string_count(argv[1], ',') != 5) {
        client->messages->add(
            client->messages, string_format(MESSAGE_ERROR_ARGUMENTS));

        return (CODE_ERROR);
    }

    return (CODE_SUCCESS);
}

void port_extract_information(
    const char *information, uint32_t *addr, uint16_t *port)
{
    char **args = args_create(information, ",");
    char *address =
        string_format("%s.%s.%s.%s", args[0], args[1], args[2], args[3]);

    *addr = inet_addr(address);
    *port = (strtol(args[4], NULL, 10) * 256) + strtol(args[5], NULL, 10);
}

char *port_message()
{
    char *message = string_format(MESSAGE_SUCCESS);

    return (message);
}

int port(server_t *server, client_t *client, int argc, char **argv)
{
    (void)(server);

    if (port_validation(client, argc, argv))
        return (CODE_ERROR);

    uint32_t addr = 0;
    uint16_t port = 0;

    port_extract_information(argv[1], &addr, &port);

    client->con_data = socket_create_p(addr, PF_INET, port);
    client->mode = TRANSFER_ACTIVE;

    client->messages->add(client->messages, port_message());

    return (CODE_SUCCESS);
}