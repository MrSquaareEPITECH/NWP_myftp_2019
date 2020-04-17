/*
** EPITECH PROJECT, 2020
** server
** File description:
** message_list.h
*/

#ifndef SERVER_SRC_MESSAGE_LIST_H
#define SERVER_SRC_MESSAGE_LIST_H

#include <stddef.h>

typedef struct message_list_s message_list_t;
typedef struct message_chain_s message_chain_t;

struct message_chain_s {
    char *message;
    message_chain_t *next;
};

struct message_list_s {
    message_chain_t *begin;
    message_chain_t *end;

    int (*add)(message_list_t *this, char *message);
    int (*remove)(message_list_t *this, char *message);
    size_t (*size)(message_list_t *this);
};

message_list_t *message_list_create(void);
void message_list_delete(message_list_t *list);

#endif // SERVER_SRC_MESSAGE_LIST_H
