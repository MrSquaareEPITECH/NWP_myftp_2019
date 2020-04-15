/*
** EPITECH PROJECT, 2020
** server
** File description:
** message_list.c
*/

#include "message_list.h"

#include <stdlib.h>

#include "def/code.h"

static int message_list_add(message_list_t* this, char* message)
{
    message_chain_t* item = malloc(sizeof(message_chain_t));

    if (item == NULL)
        return (CODE_ERROR);

    item->message = message;
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

static int message_list_remove(message_list_t* this, char* message)
{
    if (this->begin->message == message) {
        this->begin = this->begin->next;

        return (CODE_SUCCESS);
    }

    message_chain_t* parent = this->begin;
    message_chain_t* child = parent->next;

    for (; child && (child->message != message);
         parent = parent->next, child = parent->next)
        ;

    if (child == NULL)
        return (CODE_ERROR);

    parent->next = child->next;

    if (this->end == child)
        this->end = parent;

    return (CODE_SUCCESS);
}

static size_t message_list_size(message_list_t* this)
{
    size_t size = 0;

    for (const message_chain_t* chain = this->begin; chain;
         ++size, chain = chain->next)
        ;

    return (size);
}

message_list_t* message_list_create()
{
    message_list_t* list = malloc(sizeof(message_list_t));

    if (list == NULL)
        return (NULL);

    list->begin = NULL;
    list->end = NULL;

    list->add = message_list_add;
    list->remove = message_list_remove;
    list->size = message_list_size;

    return list;
}

void message_list_delete(message_list_t* list)
{
    if (list == NULL)
        return;

    for (message_chain_t* chain = list->begin; chain;) {
        message_chain_t* current = chain;

        chain = chain->next;

        free(current->message);
        free(current);
    }

    free(list);
}