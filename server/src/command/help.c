/*
** EPITECH PROJECT, 2020
** server
** File description:
** help.c
*/

#include "help.h"

#include "def/code.h"
#include "def/command.h"
#include "def/message.h"
#include "helper/command.h"
#include "util/string.h"

static int help_validation(client_t *client, int argc, char **argv)
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

char *help_message_all()
{
    char *commands = "NULL"; // TODO: Support

    char *message =
        string_format("%s %s %s", MESSAGE_HELP, commands, MESSAGE_HELP_END);

    return (message);
}

char *help_message_command(const char *name)
{
    const command_t *command = command_find(name);

    char *message = string_format("%s %s - %s %s", MESSAGE_HELP_COMMAND,
        command->name, command->help, MESSAGE_HELP_END);

    return (message);
}

int help(server_t *server, client_t *client, int argc, char **argv)
{
    (void)(server);

    if (help_validation(client, argc, argv))
        return (CODE_ERROR);

    if (argc == 1)
        client->messages->add(client->messages, help_message_all());
    else
        client->messages->add(client->messages, help_message_command(argv[1]));

    return (CODE_SUCCESS);
}