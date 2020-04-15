/*
** EPITECH PROJECT, 2020
** server
** File description:
** command.h
*/

#ifndef SERVER_SRC_HELPER_COMMAND_H
#define SERVER_SRC_HELPER_COMMAND_H

#include <string.h>

#include "def/command.h"
#include "type/command.h"

const command_t *command_find(const char *name);

#endif // SERVER_SRC_HELPER_COMMAND_H
