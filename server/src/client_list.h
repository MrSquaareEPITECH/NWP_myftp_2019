/*
** EPITECH PROJECT, 2020
** server
** File description:
** client_list.h
*/

#ifndef SERVER_SRC_CLIENT_LIST_H
#define SERVER_SRC_CLIENT_LIST_H

#include "client.h"

typedef struct client_list_s client_list_t;
typedef struct client_chain_s client_chain_t;

struct client_chain_s {
    client_t *client;
    client_chain_t *next;
};

struct client_list_s {
    client_chain_t *begin;
    client_chain_t *end;

    int (*add)(client_list_t *this, client_t *client);
    int (*remove)(client_list_t *this, client_t *client);
    size_t (*size)(client_list_t *this);
};

client_list_t *client_list_create(void);
void client_list_delete(client_list_t *list);

#endif // SERVER_SRC_CLIENT_LIST_H
