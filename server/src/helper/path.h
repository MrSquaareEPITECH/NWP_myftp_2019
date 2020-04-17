/*
** EPITECH PROJECT, 2020
** server
** File description:
** path.h
*/

#ifndef SERVER_SRC_HELPER_PATH_H
#define SERVER_SRC_HELPER_PATH_H

#include "component/client/client.h"
#include "component/server/server.h"

char *path_find(server_t *server, client_t *client, char *dir);

#endif // SERVER_SRC_HELPER_PATH_H
