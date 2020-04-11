/*
** EPITECH PROJECT, 2020
** server
** File description:
** client_list.c
*/

#include "client_list.h"

#include <stdlib.h>

#include "def/code.h"

static int client_list_add(client_list_t* this, client_t* client)
{
    client_chain_t* item = malloc(sizeof(client_chain_t));

    if (item == NULL)
        return (CODE_ERROR);

    item->client = client;
    item->next = NULL;

    if (this->begin == NULL) {
        this->begin = item;
        this->end = item;

        return (CODE_SUCCESS);
    }

    this->end->next = item;
    this->end = item;

    return (CODE_SUCCESS);
}

static int client_list_remove(client_list_t* this, client_t* client)
{
    if (this->begin->client == client) {
        this->begin = this->begin->next;

        return (CODE_SUCCESS);
    }

    client_chain_t* parent = this->begin;
    client_chain_t* child = parent->next;

    for (; child && (child->client != client);
         parent = parent->next, child = parent->next)
        ;

    if (child == NULL)
        return (CODE_ERROR);

    parent->next = child->next;

    if (this->end == child)
        this->end = parent;

    return (CODE_SUCCESS);
}

static size_t client_list_size(client_list_t* this)
{
    size_t size = 0;

    for (const client_chain_t* chain = this->begin; chain;
         ++size, chain = chain->next)
        ;

    return (size);
}

client_list_t* client_list_create()
{
    client_list_t* list = malloc(sizeof(client_list_t));

    if (list == NULL)
        return (NULL);

    list->begin = NULL;
    list->end = NULL;

    list->add = client_list_add;
    list->remove = client_list_remove;
    list->size = client_list_size;

    return list;
}

void client_list_delete(client_list_t* list)
{
    if (list == NULL)
        return;

    for (client_chain_t* chain = list->begin; chain;) {
        client_chain_t* current = chain;

        chain = chain->next;

        client_delete(current->client);
        free(current);
    }

    free(list);
}