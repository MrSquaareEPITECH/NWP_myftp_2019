/*
** EPITECH PROJECT, 2020
** server
** File description:
** command.h
*/

#ifndef SERVER_SRC_DEF_COMMAND_H
#define SERVER_SRC_DEF_COMMAND_H

#include "command/pasv.h"
#include "command/port.h"
#include "command/quit.h"
#include "command/retr.h"
#include "command/stor.h"
#include "type/command.h"

static const command_t COMMANDS[] = {
    {"PASV", pasv},
    {"PORT", port},
    {"QUIT", quit},
    {"RETR", retr},
    {"STOR", stor},
    {NULL, NULL}
};

#endif // SERVER_SRC_DEF_COMMAND_H
