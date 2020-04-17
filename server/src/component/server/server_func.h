/*
** EPITECH PROJECT, 2020
** server
** File description:
** server_func.h
*/

#ifndef SERVER_SRC_COMPONENT_SERVER_SERVER_FUNC_H
#define SERVER_SRC_COMPONENT_SERVER_SERVER_FUNC_H

#include "server.h"

int server_accept(server_t* this);
int server_execute(server_t* this);
int server_listen(server_t* this);
int server_select(server_t* this);
int server_run(server_t* this);

#endif // SERVER_SRC_COMPONENT_SERVER_SERVER_FUNC_H
