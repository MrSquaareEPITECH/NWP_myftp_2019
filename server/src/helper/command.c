/*
** EPITECH PROJECT, 2020
** server
** File description:
** command.c
*/

#include "command.h"

const command_t *command_find(const char *name)
{
    const command_t *command = NULL;

    for (size_t i = 0; COMMANDS[i].name; ++i) {
        if (strcasecmp(COMMANDS[i].name, name) == 0) {
            command = &COMMANDS[i];

            break;
        }
    }

    return (command);
}