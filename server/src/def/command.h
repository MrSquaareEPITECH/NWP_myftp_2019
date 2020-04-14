/*
** EPITECH PROJECT, 2020
** server
** File description:
** command.h
*/

#ifndef SERVER_SRC_DEF_COMMAND_H
#define SERVER_SRC_DEF_COMMAND_H

#include <stddef.h>

#include "command/help.h"
#include "command/pass.h"
#include "command/pasv.h"
#include "command/port.h"
#include "command/pwd.h"
#include "command/quit.h"
#include "command/retr.h"
#include "command/stor.h"
#include "command/user.h"
#include "type/command.h"

static const command_t COMMANDS[] = {{"HELP", HELP_HELP, help},
    {"PASS", HELP_PASS, pass}, {"PASV", HELP_PASV, pasv},
    {"PORT", HELP_PORT, port}, {"PWD", HELP_PWD, pwd},
    {"QUIT", HELP_QUIT, quit}, {"RETR", HELP_RETR, retr},
    {"STOR", HELP_STOR, stor}, {"USER", HELP_USER, user}, {NULL, NULL, NULL}};

#endif // SERVER_SRC_DEF_COMMAND_H
