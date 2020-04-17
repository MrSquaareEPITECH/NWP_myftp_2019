/*
** EPITECH PROJECT, 2020
** server
** File description:
** client_func.h
*/

#ifndef SERVER_SRC_COMPONENT_CLIENT_CLIENT_FUNC_H
#define SERVER_SRC_COMPONENT_CLIENT_CLIENT_FUNC_H

#include "client.h"

int client_download(client_t *client, int dest);
int client_receive(client_t *client, char *buf, size_t count);
int client_send(client_t *client, const char *buf, size_t count);
int client_upload(client_t *client, int src);

#endif // SERVER_SRC_COMPONENT_CLIENT_CLIENT_FUNC_H
