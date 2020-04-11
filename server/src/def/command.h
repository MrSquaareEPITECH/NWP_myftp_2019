/*
** EPITECH PROJECT, 2020
** server
** File description:
** command.h
*/

#ifndef SERVER_SRC_DEF_COMMAND_H
#define SERVER_SRC_DEF_COMMAND_H

#include "command/quit.h"
#include "type/command.h"

static const command_t COMMANDS[] = {
    {"QUIT\r\n", quit},
    {NULL, NULL}
};

#endif // SERVER_SRC_DEF_COMMAND_H
