/*
** EPITECH PROJECT, 2020
** server
** File description:
** command.h
*/

#ifndef SERVER_SRC_DEF_COMMAND_H
#define SERVER_SRC_DEF_COMMAND_H

#include <stddef.h>

#include "command/cdup.h"
#include "command/cwd.h"
#include "command/dele.h"
#include "command/help.h"
#include "command/list.h"
#include "command/noop.h"
#include "command/pass.h"
#include "command/pasv.h"
#include "command/port.h"
#include "command/pwd.h"
#include "command/quit.h"
#include "command/retr.h"
#include "command/stor.h"
#include "command/user.h"
#include "type/command.h"

static const command_t COMMANDS[] = {{"CDUP", HELP_CDUP, cdup},
    {"CWD", HELP_CWD, cwd}, {"DELE", HELP_DELE, dele},
    {"HELP", HELP_HELP, help}, {"LIST", HELP_LIST, list},
    {"NOOP", HELP_NOOP, noop}, {"PASS", HELP_PASS, pass},
    {"PASV", HELP_PASV, pasv}, {"PORT", HELP_PORT, port},
    {"PWD", HELP_PWD, pwd}, {"QUIT", HELP_QUIT, quit},
    {"RETR", HELP_RETR, retr}, {"STOR", HELP_STOR, stor},
    {"USER", HELP_USER, user}, {NULL, NULL, NULL}};

#endif // SERVER_SRC_DEF_COMMAND_H
