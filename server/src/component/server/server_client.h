/*
** EPITECH PROJECT, 2020
** server
** File description:
** server_client.h
*/

#ifndef SERVER_SRC_COMPONENT_SERVER_SERVER_CLIENT_H
#define SERVER_SRC_COMPONENT_SERVER_SERVER_CLIENT_H

#include "server.h"

int server_client_add(server_t* this, client_t* client);
int server_client_call_command(server_t* this, client_t* client);
int server_client_send_message(server_t* this, client_t* client);
int server_client_remove(server_t* this, client_t* client);

#endif // SERVER_SRC_COMPONENT_SERVER_SERVER_CLIENT_H
